public class Primos_100 {

    public static void main(String[] args) {

        int flag = 1, cont = 0, num = 2;
        int[] Primos = new int[100];

        while (cont < 100) {
            flag = 1;
            for (int i = (num - 1); i >= 2; i--) {
                if (num % i == 0) {
                    flag = 0;
                }
            }
            if (flag == 1) {
                Primos[cont] = num;
                cont++;
            }
                num++;
        }

        for(int i = 0 ; i < 100; i++)
        {
            System.out.println("numero " + Primos[i] + " e sua posicao =  " + (i + 1) +"\n");
        }
        

    }
}
