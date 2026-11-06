
public class Principal {
    public static void main(String[] args) {
        Aluno Luiz = new Aluno(1, "Luiz Andre");
        Aluno Abelardo = new Aluno(2, "abelardo");
        Aluno Teyllor = new Aluno(3, "Teyllor");

        System.out.println(Teyllor.nome + " " + Teyllor.codigo);
        System.out.println(Operacoes.soma(1,2));
    }
}
0