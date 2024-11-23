#include "../fn.hpp"
#include "student.hpp"

int main() {
    Student stu;

    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "show")  { stu.show();                          }
        else if (args[0] == "enter") { stu.enter();                         } 
        else if (args[0] == "leave") { stu.leave();                         }
        else if (args[0] == "fuel")  { stu.fuel(+args[1]);                  }
        else if (args[0] == "drive") { stu.drive(+args[1]);                 }

        else if (args[0] == "end")   { break;                               }
        else                         { fn::write("fail: comando invalido"); }
    }
}
