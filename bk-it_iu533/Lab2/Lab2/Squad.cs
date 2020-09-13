using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2 {
    class Squad: Rectangle, IPrint {
        public Squad(double size)
            : base(size, size) {
            this.Type="Квадрат";
        }

        public override string ToString() {
            return this.Type + " со стороной "
                + this.width.ToString()
                + ", площадью: " + this.Area().ToString();
        }
    }
}


