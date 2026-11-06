public class Subtracao{ //clase
    //atributos privados
    private int a; 
    private int b ;
    private int r ;

    //metodos publicos
    public void init (int x, int y){
    this.a = x;
    this.b = y;
    System.out.println("Valores foram recebidos!!\n" + "a = " + x + ", b = " + y);
    }
    public void fazoperacao (){
        this.r = this.a - this.b;
        System.out.println("Valores foram subtraidos !!\n");
    }
    public int getres(){
        return this.r;
    }
}

