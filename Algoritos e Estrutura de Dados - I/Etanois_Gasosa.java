import java.util.Scanner;

public class Etanois_Gasosa{
    public static void main(String[] args) {
        float etanois, gasosa, diferenca;
        Scanner input = new Scanner(System.in);

        System.out.println("Digite o valor do Etanois : ");
        etanois = input.nextFloat();

        System.out.println("Digite o valor do Gasosa : ");
        gasosa = input.nextFloat();

        diferenca = etanois / gasosa;
        
        if (diferenca > 0.7)
            System.out.println("vale mais a pena a Gasosa");
        else if (diferenca < 0.7)
            System.out.println("vale mais a pena o Etanois");
        else
            System.out.println("Os dois tem o mesmo valor, va no mais barato!!");

        input.close();
    }

}
