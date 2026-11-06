
public class Main{
    public static void main(String[] args)
{
    // Soma s; //Criando um ponteiro (referencia)
    //         //Para um objeto que ainda nao existe.
    // s = new Soma(); //Criando um objeto apontado por
    //                 //s.

    // s.init(10,20);
    // s.fazoperacao();
    
    // System.out.println(s.getres());

    // int res = s.getres();

    // Subtracao sub;
    // sub = new Subtracao();
    // sub.init(res, 2);
    // sub.fazoperacao();

    // System.out.println(sub.getres());

    Baskara bas, bas2;
    bas = new Baskara();
    bas2 = new Baskara();

    bas.init(1,2,5);
    bas.fazoperacao();
    bas.getres();

    System.out.println("\nEquação onde delta não da negativo");
    bas2.init(1,-5,6);
    bas2.fazoperacao();
    bas2.getres();

    //Quando o progama finaliza, ou quando o objeto
    //nao é
}
}