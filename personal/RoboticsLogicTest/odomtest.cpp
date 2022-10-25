#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double conv = (atan(1) * 4 / 180);

void field_oriented(vector<double> &nums, int angle) {
  nums[2] = nums[1] * cos(angle * conv) + nums[0] * sin(angle * conv);
  nums[3] = nums[1] * sin(angle * conv) + nums[0] * cos(angle * conv);
}

void undo_trig(vector<double> &nums, int angle) {
  nums[4] = sin(angle * conv) * nums[2] + cos(angle * conv) * (nums[3]);
  nums[5] = cos(angle * conv) * nums[2] - sin(angle * conv) * (nums[3]);
}

void pol_cart(vector<double> &nums, int angle) {
  if (angle < 90) {
    nums[4] = cos(angle * conv) * nums[2] - sin(angle * conv) * nums[3];
    nums[5] = sin(angle * conv) * nums[2] + cos(angle * conv) * nums[3];
  } else if (angle < 180) {
    nums[4] = cos(angle * conv) * nums[2] + sin(angle * conv) * nums[3];
    nums[5] = sin(angle * conv) * nums[2] - cos(angle * conv) * nums[3];
  } else if (angle < 270) {
    nums[4] = cos(angle * conv) * nums[2] - sin(angle * conv) * nums[3];
    nums[5] = sin(angle * conv) * nums[2] + cos(angle * conv) * nums[3];
  } else {
    nums[4] = cos(angle * conv) * nums[2] + sin(angle * conv) * nums[3];
    nums[5] = sin(angle * conv) * nums[2] - cos(angle * conv) * nums[3];
  }
}

// Vector is as follows:
// 0: x input
// 1: y input
// 2: x field-oriented
// 3: y field-oriented
// 4: x extracted
// 5: y extracted

void comp(vector<double> nums, int angle) {
  cout << angle << ":   (" << nums[0] << ',' << nums[1] << ")  |  " << '('
       << nums[4] << ',' << nums[5] << ")\n";
}

int main() {
  double x, y;
  vector<double> robot_moved(6);
  for (int i = 0; i < 360; i += 20) {
    for (int j = 10; j < 360; j += 20) {
      robot_moved[0] = cos(j * conv);
      robot_moved[1] = sin(j * conv);
      field_oriented(robot_moved, i);
      pol_cart(robot_moved, i);
      comp(robot_moved, i);
    }
  }
}
// For each robot angle:
// try a full circle of joystick values -> field_oriented
// take the output value and try to odom it, compare values