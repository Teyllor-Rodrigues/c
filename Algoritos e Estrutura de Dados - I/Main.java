
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite o primeiro valor: ");
        int valor1 = scanner.nextInt();

        System.out.print("Digite o segundo valor: ");
        int valor2 = scanner.nextInt();

        System.out.println("A soma é " + (valor1 + valor2));

        scanner.close();
    }
}