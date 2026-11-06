
public class Baskara {
    private int a;
    private int b;
    private int c;
    private int delta;
    private double x1;
    private double x2;

    private int verificacao() {
        int flag = 0;
        if (delta < 0) {
            System.out.println("Delta foi calculado negativo !!");
            return flag;
        } else {
            flag = 1;
            return flag;
        }

    }

    public void init(int x, int y, int z) {
        this.a = x;
        this.b = y;
        this.c = z;

        this.delta = (b * b) - (4 * a * c);
    }

    public void fazoperacao() {
        this.x1 = ((this.b * -1) + Math.sqrt(this.delta)) / 2 * this.a;
        this.x2 = ((this.b * -1) - Math.sqrt(this.delta)) / 2 * this.a;
    }

    public void getres() {
        int flag = verificacao();
        if (flag == 1) {
            System.out.println("Este é o valor do x1 = " + x1);
            System.out.println("\nEste é o valor do x2 = " + x2);
        }
    }

}
