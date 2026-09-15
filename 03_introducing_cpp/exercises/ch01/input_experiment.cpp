#include <iostream>
#include <limits>

// int main() {
//   const double largest = std::numeric_limits<double>::max();
//   std::cout << "please enter a number up to " << largest << ".\n";
//   double number{};
//   std::cin >> number;
//   std::cout << number << '\n';
//   if (!std::cin.eof() && std::cin.peek() != '\n') {
//     std::cout << "unused input\n";
//   }
// }

int main() {
  std::cout << "please enter a number.\n";
  int number{};
  std::cin >> number;
  if (std::cin)
    std::cout << number << '\n';
  else
    std::cout << "something went wrong";
}
