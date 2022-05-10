// Drew Friend
// 4/6/22
// Memory Lab:
//

// Breaking down the immediate bits/explaining where they come from is for my own benefit
// not to count as my "explaining the code", per the assignment
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

// Base Code
const int MEM_SIZE = 1 << 18;
const int NUM_REGS = 32;

// Code from Fetch portion
struct FetchOut
{
   uint32_t instruction;

   // The code below allows us to cout a FetchOut structure.
   // We can use this to debug our code.
   // FetchOut fo = { 0xdeadbeef };
   // cout << fo << '\n';
   friend ostream &operator<<(ostream &out, const FetchOut &fo)
   {
      ostringstream sout;
      sout << "0x" << hex << setfill('0') << right << setw(8) << fo.instruction;
      return out << sout.str();
   }
};

// Code from Decode portion
enum OpcodeCategories
{
   LOAD,
   STORE,
   BRANCH,
   JALR,
   JAL,
   OP_IMM,
   OP,
   AUIPC,
   LUI,
   OP_IMM_32,
   OP_32,
   SYSTEM,
   UNIMPL
};
const OpcodeCategories OPCODE_MAP[4][8] = {
    // First row (inst[6:5] = 0b00)
    {LOAD, UNIMPL, UNIMPL, UNIMPL, OP_IMM, AUIPC, OP_IMM_32, UNIMPL},
    // Second row (inst[6:5] = 0b01)
    {STORE, UNIMPL, UNIMPL, UNIMPL, OP, LUI, OP_32, UNIMPL},
    // Third row (inst[6:5] = 0b10)
    {UNIMPL, UNIMPL, UNIMPL, UNIMPL, UNIMPL, UNIMPL, UNIMPL, UNIMPL},
    // Fourth row (inst[6:5] = 0b11)
    {BRANCH, JALR, UNIMPL, JAL, SYSTEM, UNIMPL, UNIMPL, UNIMPL}};
struct DecodeOut
{
   OpcodeCategories op;
   uint8_t rd;
   uint8_t funct3;
   uint8_t funct7;
   int64_t offset;    // Offsets for BRANCH and STORE
   int64_t left_val;  // typically the value of rs1
   int64_t right_val; // typically the value of rs2 or immediate

   friend ostream &operator<<(ostream &out, const DecodeOut &dec)
   {
      ostringstream sout;
      sout << "Operation: ";
      switch (dec.op)
      {
      case LUI:
         sout << "LUI";
         break;
      case AUIPC:
         sout << "AUIPC";
         break;
      case LOAD:
         sout << "LOAD";
         break;
      case STORE:
         sout << "STORE";
         break;
      case OP_IMM:
         sout << "OPIMM";
         break;
      case OP_IMM_32:
         sout << "OPIMM32";
         break;
      case OP:
         sout << "OP";
         break;
      case OP_32:
         sout << "OP32";
         break;
      case BRANCH:
         sout << "BRANCH";
         break;
      case JALR:
         sout << "JALR";
         break;
      case JAL:
         sout << "JAL";
         break;
      case SYSTEM:
         sout << "SYSTEM";
         break;
      case UNIMPL:
         sout << "NOT-IMPLEMENTED";
         break;
      }
      sout << '\n';
      sout << "RD       : " << (uint32_t)dec.rd << '\n';
      sout << "funct3   : " << (uint32_t)dec.funct3 << '\n';
      sout << "funct7   : " << (uint32_t)dec.funct7 << '\n';
      sout << "offset   : " << dec.offset << '\n';
      sout << "left     : " << dec.left_val << '\n';
      sout << "right    : " << dec.right_val;
      return out << sout.str();
   }
};

// Code from the execute portion
enum AluCommands
{
   ALU_ADD,
   ALU_SUB,
   ALU_MUL,
   ALU_DIV,
   ALU_REM,
   ALU_SLL,
   ALU_SRL,
   ALU_SRA,
   ALU_AND,
   ALU_OR,
   ALU_XOR,
   ALU_NOT
};
struct ExecuteOut
{
   int64_t result;
   uint8_t n, z, c, v;

   friend ostream &operator<<(ostream &out, const ExecuteOut &eo)
   {
      ostringstream sout;
      sout << "Result: " << eo.result << " [NZCV]: "
           << (uint32_t)eo.n
           << (uint32_t)eo.z
           << (uint32_t)eo.c
           << (uint32_t)eo.v;
      return out << sout.str();
   }
};

// Code from the memory portion
struct MemoryOut
{
   int64_t value;

   friend ostream &operator<<(ostream &out, const MemoryOut &mo)
   {
      ostringstream sout;
      sout << "0x" << hex << right << setfill('0') << setw(16) << mo.value;
      return out << sout.str();
   }
};

class Machine
{
   char *mMemory;           // The memory.
   int mMemorySize;         // The size of the memory (should be MEM_SIZE)
   int64_t mPC;             // The program counter
   int64_t mRegs[NUM_REGS]; // The register file

   FetchOut mFO;   // Result of the fetch()   method.
   DecodeOut mDO;  // Result of the decode()  method.
   ExecuteOut mEO; // Result of the execute() method.
   MemoryOut mMO;  // Result of the memory()  method.

   // Read from the internal memory
   // Usage:
   // int myintval = memory_read<int>(0); // Read the first 4 bytes
   // char mycharval = memory_read<char>(8); // Read byte index 8
   template <typename T>
   T memory_read(int64_t address) const
   {
      return *reinterpret_cast<T *>(mMemory + address);
   }

   // Write to the internal memory
   // Usage:
   // memory_write<int>(0, 0xdeadbeef); // Set bytes 0, 1, 2, 3 to 0xdeadbeef
   // memory_write<char>(8, 0xff);      // Set byte index 8 to 0xff
   template <typename T>
   void memory_write(int64_t address, T value)
   {
      *reinterpret_cast<T *>(mMemory + address) = value;
   }

   // Copies the value at the specified index across the rest of the number
   int64_t sign_extend(int64_t value, int8_t index)
   {
      if ((value >> index) & 1)
      {
         // Sign bit is 1
         return value | (-1L << index);
      }
      else
      {
         // Sign bit is 0
         return value & ~(-1UL << index);
      }
   }

   // Decode an instruction based on type of byte
   void decode_r() // Used for OP_32
   {
      // Main difference from B is the rd and funct7 instead of immediate values
      mDO.rd = (mFO.instruction >> 7) & 0x1f;
      mDO.funct3 = (mFO.instruction >> 12) & 7;
      mDO.left_val = get_xreg(mFO.instruction >> 15); // get_xreg truncates for us
      mDO.right_val = get_xreg(mFO.instruction >> 20);
      mDO.funct7 = (mFO.instruction >> 25) & 0x7f;
   }
   void decode_i() // Used for Load, JALR, OP_IMM, SYSTEM, and OP_IMM_32
   {
      // I has an rd instead of immediate values, but is lacking a right value in favor of more immediate digits, all sequentially
      mDO.rd = (mFO.instruction >> 7) & 0x1f;
      mDO.funct3 = (mFO.instruction >> 12) & 7;
      mDO.left_val = get_xreg(mFO.instruction >> 15);           // get_xreg truncates for us
      mDO.right_val = sign_extend((mFO.instruction >> 20), 11); // 0-11 from 20-31
   }
   void decode_s() // Used for Store
   {
      // Only real difference from B is that the immediate is more sequential and uses 0-11 instead of 1-12
      mDO.funct3 = (mFO.instruction >> 12) & 7;
      mDO.left_val = get_xreg(mFO.instruction >> 15); // get_xreg truncates for us
      mDO.right_val = get_xreg(mFO.instruction >> 20);
      mDO.offset = sign_extend((((mFO.instruction >> 25) & 0x7f) << 5) | // 5-11 from 25-31
                                   (((mFO.instruction >> 7) & 0x1f)),    // 0-4  from 7-11
                               11);
   }
   void decode_b() // Used for Branch
   {
      // mDO.rd        = (mFO.instruction >> 7) & 0x1f; //It doesn't look like b uses RD?
      // This code was given, and was the code the other decodes were based off of
      mDO.funct3 = (mFO.instruction >> 12) & 7;
      mDO.left_val = get_xreg(mFO.instruction >> 15); // get_xreg truncates for us
      mDO.right_val = get_xreg(mFO.instruction >> 20);
      mDO.offset = sign_extend((((mFO.instruction >> 31) & 1) << 12) |       // 12   from 31
                                   (((mFO.instruction >> 7) & 1) << 11) |    // 11   from 7
                                   (((mFO.instruction >> 25) & 0x3f) << 5) | // 5-10 from 25-30
                                   (((mFO.instruction >> 8) & 0xf) << 1),    // 1-4  from 8 -11
                               12);
   }
   void decode_u() // Used for AUIPC, LUI
   {
      // THis one is real easy. RD is in the same space it was listed for B, and the offset maps over exactly
      mDO.rd = (mFO.instruction >> 7) & 0x1f;
      mDO.offset = sign_extend(mFO.instruction & 0xFFFFF000, 31); // 12-31 from 12-31
   }
   void decode_j() // Used for JAL
   {
      // Similar to U, except the bits are "swizzled"
      mDO.rd = (mFO.instruction >> 7) & 0x1f;
      mDO.offset = sign_extend((((mFO.instruction >> 31) & 1) << 20) |        // 20    from 31
                                   (((mFO.instruction >> 12) & 0xff) << 12) | // 12-19 from 12-19
                                   (((mFO.instruction >> 20) & 1) << 11) |    // 11    from 20
                                   (((mFO.instruction >> 21) & 0x3ff) << 1)   // 1-10  from 21-30
                               ,
                               20);
   }

   // Execute an instruction given ALU command and inputs
   ExecuteOut alu(AluCommands cmd, int64_t left, int64_t right)
   {
      ExecuteOut ret;
      switch (cmd)
      {
      case ALU_ADD:
         ret.result = left + right;
         break;
      case ALU_SUB:
         ret.result = left - right;
         break;
      case ALU_MUL:
         ret.result = left * right;
         break;
      case ALU_DIV:
         ret.result = left / right;
         break;
      case ALU_REM:
         ret.result = left % right;
         break;
      case ALU_SLL:
         ret.result = left << right;
         break;
      case ALU_SRL:
         ret.result = static_cast<uint64_t>(left) >> right;
         break;
      case ALU_SRA:
         ret.result = left >> right;
         break;
      case ALU_AND:
         ret.result = left & right;
         break;
      case ALU_OR:
         ret.result = left | right;
         break;
      case ALU_XOR:
         ret.result = left ^ right;
         break;
      case ALU_NOT:
         ret.result = ~left;
         break;
      }
      // Now that we have the result, determine the flags.
      uint8_t sign_left = (left >> 63) & 1;
      uint8_t sign_right = (right >> 63) & 1;
      uint8_t sign_result = (ret.result >> 63) & 1;
      ret.z = !ret.result;
      ret.n = sign_result;
      ret.v = ~sign_left & ~sign_right & sign_result |
              sign_left & sign_right & ~sign_result;
      ret.c = (ret.result > left) || (ret.result > right);
      return ret;
   }

public:
   // Base code that came with the class, utility functions
   Machine(char *mem, int size)
   {
      mMemory = mem;
      mMemorySize = size;
      mPC = 0;
      set_xreg(2, mMemorySize);
   }
   int64_t get_pc() const
   {
      return mPC;
   }
   void set_pc(int64_t to)
   {
      mPC = to;
   }
   int64_t get_xreg(int which) const
   {
      which &= 0x1f; // Make sure the register number is 0 - 31
      return mRegs[which];
   }
   void set_xreg(int which, int64_t value)
   {
      which &= 0x1f;
      mRegs[which] = value;
   }

   // Code from Fetch portion: Involves getting a single instruction from "RAM"
   void fetch()
   {
      // mFO.instruction = 0x02A9DF33;
      mFO.instruction = memory_read<uint32_t>(mPC);
   }
   FetchOut &debug_fetch_out()
   {
      return mFO;
   }

   // Code from Decode portion: Involves breaking hex instruction down into pieces
   void decode()
   {
      uint8_t opcode_map_row = (mFO.instruction >> 5) & 3;
      uint8_t opcode_map_col = (mFO.instruction >> 2) & 7;
      uint8_t inst_size = mFO.instruction & 3;
      if (inst_size != 3)
      {
         cerr << "[DECODE] Invalid instruction (not a 32-bit instruction).\n";
         return;
      }
      mDO.op = OPCODE_MAP[opcode_map_row][opcode_map_col];
      // Decode the rest of mDO based on the instruction type
      switch (mDO.op)
      {
      case SYSTEM:
      case LOAD:
      case JALR:
      case OP_IMM:
      case OP_IMM_32:
         decode_i();
         break;
      case STORE:
         decode_s();
         break;
      case BRANCH:
         decode_b();
         break;
      case JAL:
         decode_j();
         break;
      case AUIPC:
      case LUI:
         decode_u();
         break;
      case OP:
      case OP_32:
         decode_r();
         break;
      default:
         cerr << "Invalid op type: " << mDO.op << '\n';
         break;
      }
   }
   DecodeOut &debug_decode_out()
   {
      return mDO;
   }

   // Code from the Execute portion: Involves converting instructions to ALU and calculating result/flags
   void execute()
   {
      AluCommands cmd;
      // Most instructions will follow left/right
      // but some won't, so we need these:
      int64_t op_left = mDO.left_val;
      int64_t op_right = mDO.right_val;

      if (mDO.op == BRANCH)
      {
         // A branch needs to subtract the operands
         cmd = ALU_SUB;
      }
      else if (mDO.op == LOAD || mDO.op == STORE)
      {
         // For loads and stores, we need to add the
         // offset with the base register.
         cmd = ALU_ADD;
         op_right = (mDO.op == LOAD) ? op_right : mDO.offset;
      }
      else if (mDO.op == OP)
      {
         // We can't tell which ALU command to use until
         // we read the funct3 and funct7
         switch (mDO.funct3)
         {
         case 0b000: // ADD, SUB, or MUL
            if (mDO.funct7 == 0)
            {
               cmd = ALU_ADD;
            }
            else if (mDO.funct7 == 32)
            {
               cmd = ALU_SUB;
            }
            else if (mDO.funct7 == 1)
            {
               cmd = ALU_MUL;
            }
            break;
         case 0b001: // Shift Left Logical
            cmd = ALU_SLL;
            break;
         case 0b100: // XOR or DIV
            if (mDO.funct7 == 0)
            { 
               cmd = ALU_XOR;
            }
            else if (mDO.funct7 == 1)
            {
               cmd = ALU_DIV;
            }
            break;
         case 0b101: // Right Shift, Arithmatic or Logical
            if (mDO.funct7 == 0)
            {
               cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32)
            {
               cmd = ALU_SRA;
            }
            break;
         case 0b110: // OR or REM
            if (mDO.funct7 == 0)
            { 
               cmd = ALU_OR;
            }
            else if (mDO.funct7 == 1)
            {
               cmd = ALU_REM;
            }
            break;
         case 0b111: // AND
            cmd = ALU_AND;
            break;
         }
      }
      else if (mDO.op == OP_IMM)
      {
         // Look and see which ALU op needs to be executed.
         switch (mDO.funct3)
         {
         case 0b000: // ADD, there are not subtraction functions for immediates.
            cmd = ALU_ADD;
            break;
         case 0b001: // Shift Left Logical
            cmd = ALU_SLL;
            break;
         case 0b100: // XOR
            cmd = ALU_XOR;
            break;
         case 0b101: // Right Shift, Arithmatic or Logical
            if (mDO.funct7 == 0)
            {
               cmd = ALU_SRL;
            }
            else if (mDO.funct7 == 32)
            {
               cmd = ALU_SRA;
            }
            break;
         case 0b110: // OR
            cmd = ALU_OR;
            break;
         case 0b111: // AND
            cmd = ALU_AND;
            break;
         }
      }
      else if (mDO.op == JALR)
      {
         // JALR has an offset and a register value that
         // need to be added together.
         mDO.left_val = 0;
         cmd = ALU_ADD;
      }
      else if (mDO.op == LUI) 
      {
         mDO.left_val = 0;
         cmd = ALU_ADD;
      }
      else if (mDO.op == AUIPC) 
      {
         mDO.left_val = mPC;
         cmd = ALU_ADD;
      }
      else if (mDO.op == JAL) 
      {
         mDO.left_val = mPC;
         cmd = ALU_ADD;
      }
      else if (mDO.op == SYSTEM) 
      {
        if(mDO.funct3 == 0b000 && mDO.funct7 == 0b0000000)
        {
           cmd = ALU_ADD;
        }
      }
      mEO = alu(cmd, op_left, op_right);
   }
   ExecuteOut &debug_execute_out()
   {
      return mEO;
   }

   // Code from the Memory portion:
   void memory()
   {
      // Store the appropriate number of bits
      if (mDO.op == STORE)
      {
         switch (mDO.funct3)
         {
         case 0b000: // SB
            memory_write<uint8_t>(mEO.result, mDO.right_val);
            break;
         case 0b001: // SH
            memory_write<uint16_t>(mEO.result, mDO.right_val);
            break;
         case 0b010: // SW
            memory_write<uint32_t>(mEO.result, mDO.right_val);
            break;
         case 0b011: // SD
            memory_write<uint64_t>(mEO.result, mDO.right_val);
            break;
         default:
            cerr << "[MEMORY: STORE]: Invalid funct3: " << mDO.funct3 << '\n';
            break;
         }
      }
      // Load the appropriate number of bits, as the right datatype
      else if (mDO.op == LOAD)
      {
         switch (mDO.funct3)
         {
         case 0b000: // LB
            mMO.value = memory_read<int8_t>(mEO.result);
            break;
         case 0b001: // LH
            mMO.value = memory_read<int16_t>(mEO.result);
            break;
         case 0b010: // LW
            mMO.value = memory_read<int32_t>(mEO.result);
            break;
         case 0b011: // LD
            mMO.value = memory_read<int64_t>(mEO.result);
            break;
         case 0b100: // LBU
            mMO.value = memory_read<uint8_t>(mEO.result);
            break;
         case 0b101: // LHU
            mMO.value = memory_read<uint16_t>(mEO.result);
            break;
         case 0b110: // LWU
            mMO.value = memory_read<uint32_t>(mEO.result);
            break;
         default:
            cerr << "[MEMORY: LOAD]: Invalid funct3: " << mDO.funct3 << '\n';
            break;
         }
      }
      else
      {
         // If this is not a LOAD or STORE, then this stage just copies
         // the ALU result.
         mMO.value = mEO.result;
      }
   }
   MemoryOut &debug_memory_out()
   {
      return mMO;
   }
};

int main(int argc, char **argv)
{
   // Initializations
   ifstream fin;
   char mem[MEM_SIZE];
   char *ptr = mem;
   Machine mach(mem, MEM_SIZE);

   // Check for problems in:
   //  arguements
   //  file name
   //  file length
   if (argc == 1)
   {
      cout << "Error: Incorrect number of arguments. \n";
      return 1;
   }
   fin.open(argv[1], ios::binary);
   if (!fin)
   {
      cout << "Error: File could not be opened. \n";
      return 1;
   }
   // Find the end of the file and check how far it is from the start
   fin.seekg(0, fin.end);
   int len = fin.tellg();
   fin.seekg(0, fin.beg);
   if (len % 4)
   {
      cout << "Error: File length " << len << " indicates error. \n";
      return 1;
   }

   // Reading the file into "ram" buffer
   fin.read(ptr, len);
   fin.close();

   // Debugging
   while (mach.get_pc() < len)
   {
      // Fetch an instruction into RAM and print HEX
      mach.fetch();
      //cout << mach.debug_fetch_out() << '\n';

      // Break down the instruction into arguements and print details
      mach.decode();
      cout << mach.debug_decode_out() << '\n';

      // Calculate the required math and print result / flags
      mach.execute();
      //cout << mach.debug_execute_out() << '\n';

      // Use memory for the load and store instructions as needed
      mach.memory();
      //cout << mach.debug_memory_out() << '\n';

      // Move to the next command
      mach.set_pc(mach.get_pc() + 4);
   }
   return 0;
}
