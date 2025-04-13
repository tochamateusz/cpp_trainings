#include <iostream>

void pass(int *p) {
  std::cout << "\t" << p << "\n";
  *p = 6;
}

struct Printer {

  std::string &internal_text;

  void modify() const { this->internal_text = "modified"; }

  void pass_string(const std::string &s) const {
    // s.append("2");
    std::cout << "In func\t" << s << "\n";
  }
};

int main(void) {
  int a = 5;
  pass(&a);
  std::cout << "test:\t" << a << "\n";

  std::string text = "test text";
  std::cout << "Main Before: \t" << text << "\n";

  text.assign("assigned");

  {
    Printer printer = Printer{.internal_text = text};
    printer.modify();
    printer.pass_string(text);
  }

  std::cout << "Main after: \t" << text << "\n";

  return 0;
}
