using System;
using System.Deployment;

namespace ConsoleApp1{
    class Program{
        static void Main(){
            while(true){
                string numb = "false";
                int D;
                int[] k = new int[3] { 0, 0, 0 };

                Console.WriteLine("Инструмент для поиска корней квадратоного уравнения.\nЧтобы выйти введите exit.\n");
                for (int i = 0; i < 3; i++){
                    Console.WriteLine("\nВведите коэффициент {0}-й уравнения: ", (i + 1).ToString());
                    numb = Console.ReadLine();
                    while (!int.TryParse(numb, out k[i])){
                        if (numb == "exit") Environment.Exit(0);
                        Console.WriteLine("\nОшибка ввода коэффициента, повторите ввод: ");
                        numb = Console.ReadLine();

                    }
                }

                D = k[1] * k[1] - 4 * k[0] * k[2];
                if (D >= 0){
                   Console.WriteLine("Ваш корень/корни: {0}",((-k[1] + D) / 2 * k[0]).ToString());
                    if(D>0)
                        Console.WriteLine(", {0}",((-k[1] + D) / 2 * k[0]).ToString());
                }
                else{
                    Console.WriteLine("\nДействительных корней не найдено.");
                }

                Console.WriteLine("\nХотите продолжить?\nexit-выход.\n");
                numb = Console.ReadLine();
                if (numb == "exit") Environment.Exit(0);
            }
        }
    }
}
