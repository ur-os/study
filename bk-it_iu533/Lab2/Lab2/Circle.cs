using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class Circle1:Figure,IPrint {
        public double radius { get; private set; }

        public Circle1(double r) {
            this.radius = r;
            this.Type = "Круг";
        }

        public override double Area() {
           // return Math.PI * this.radius * this.radius;  
           double Result= Math.PI * this.radius * this.radius;
           return Result;
        }
        public void Print() {
            Console.WriteLine(this.ToString());
        }
        public override string ToString() {
            return this.Type + " радиуса: " + this.radius.ToString()
                +", площадью " + this.Area().ToString();
        }
    }
}
