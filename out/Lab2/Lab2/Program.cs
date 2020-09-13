using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class Program {
        static void Main(string[] args) {
            Rectangle rect = new Rectangle(5, 4);
            Squad square = new Squad(5);
            Circle1 circle = new Circle1(5);

            rect.Print();
            square.Print();
            circle.Print();

            Console.ReadLine();
        }
    }
}
