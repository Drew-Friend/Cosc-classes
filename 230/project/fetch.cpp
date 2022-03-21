// Drew Friend
// 3/7/22
// Fetching Lab:
//    Read data into a char buffer from a binary file. 
//    Make the machine class able to interact with this
//    psuedo-ram. Basic error-checking with the input file
//    At the end of this section, the Machine has instructions loaded into it's "RAM" in hex form

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MEM_SIZE = 1 << 8;
const int NUM_REGS = 32;
struct FetchOut {
    uint32_t instruction;

    // The code below allows us to cout a FetchOut structure.
    // We can use this to debug our code.
    // FetchOut fo = { 0xdeadbeef };
    // cout << fo << '\n';
    friend ostream &operator<<(ostream &out, const FetchOut &fo) {
        ostringstream sout;
        sout << "0x" << hex << setfill('0') << right << setw(8) << fo.instruction;
        return out << sout.str();
    }
};

class Machine {
   char *mMemory;   // The memory.
   int mMemorySize; // The size of the memory (should be MEM_SIZE)
   int64_t mPC;     // The program counter
   int64_t mRegs[NUM_REGS]; // The register file

   FetchOut mFO;    // Result of the fetch() method.

   // Read from the internal memory
   // Usage:
   // int myintval = memory_read<int>(0); // Read the first 4 bytes
   // char mycharval = memory_read<char>(8); // Read byte index 8
   template<typename T>
   T memory_read(int64_t address) const {
       return *reinterpret_cast<T*>(mMemory + address);
   }

   // Write to the internal memory
   // Usage:
   // memory_write<int>(0, 0xdeadbeef); // Set bytes 0, 1, 2, 3 to 0xdeadbeef
   // memory_write<char>(8, 0xff);      // Set byte index 8 to 0xff
   template<typename T>
   void memory_write(int64_t address, T value) {
       *reinterpret_cast<T*>(mMemory + address) = value;
   }

public:
   Machine(char *mem, int size) {
      mMemory = mem;
      mMemorySize = size;
      mPC = 0;
      set_xreg(2, mMemorySize);
   }

   int64_t get_pc() const {
      return mPC;
   }
   void set_pc(int64_t to) {
      mPC = to;
   }

   int64_t get_xreg(int which) const {
      which &= 0x1f; // Make sure the register number is 0 - 31
      return mRegs[which];
   }
   void set_xreg(int which, int64_t value) {
      which &= 0x1f;
      mRegs[which] = value;
   }

   void fetch() {
      mFO.instruction = memory_read<uint32_t>(mPC);
   }
   FetchOut &debug_fetch_out() { 
      return mFO; 
   }
};


int main(int argc, char**argv) {
   //Initializations
   ifstream fin;
   char mem[MEM_SIZE];
   char *ptr = mem;
   Machine mach(mem, MEM_SIZE);

   // Check for problems in:
   //  arguements
   //  file name
   //  file length
   if(argc == 1) {
        cout << "Error: Incorrect number of arguments. \n";
        return 1;
    }
   fin.open(argv[1], ios::binary);
   if(!fin) {
        cout << "Error: File could not be opened. \n";
        return 1;
    }
   // Find the end of the file and check how far it is from the start
   fin.seekg(0, fin.end);
   int len = fin.tellg();
   fin.seekg(0, fin.beg);
   if(len%4)
    { 
        cout << "Error: File length " << len <<" indicates error. \n";
        return 1;
    }
   
   // Reading the file into "ram" buffer
   for(;fin.good(); ++ptr)
      *ptr = fin.get();
   fin.close();

   //Debugging
   while (mach.get_pc() < MEM_SIZE) {
      mach.fetch();
      cout << mach.debug_fetch_out() << '\n';
      mach.set_pc(mach.get_pc() + 4);
   }
   return 0;
}

