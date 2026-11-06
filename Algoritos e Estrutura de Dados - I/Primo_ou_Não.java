import java.util.Scanner;

public class Primo_ou_Não {
    public static void main(String[] args) {
        int num = 0, flag = 1, cont = 1;
        Scanner input = new Scanner(System.in);
        while (cont != 0) {

            flag = 1;
            System.out.println("\nDigite um numero : ");
            num = input.nextInt();

            for (int i = (num - 1); i >= 2; i--) {
                if (num % i == 0) {
                    System.out.println("O numero não é primo");
                    flag = 0;
                    break;
                }
            }

            if (num < 2) {
                flag = 0;
                System.out.println("O numero não é primo");
            }
            if (flag == 1) {
                System.out.println("o numero é primo");
            }
            cont = num;
            System.out.println();
        }
        input.close();
    }
}