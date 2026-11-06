public class Aluno {

    public static int qtd = 0; // pertence a classe, não ao objeto

    public int codigo; //atributo de instancia. Pertencem ao objeto
    public String nome; 

    Aluno(int codigo, String nome) {
        this.codigo = codigo;
        this.nome = nome;

        Aluno.qtd++;
    }

}
