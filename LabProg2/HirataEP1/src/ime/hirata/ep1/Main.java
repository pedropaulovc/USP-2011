package ime.hirata.ep1;

/**
 * @author Pedro Paulo Vezza Campos    NUSP: 7538743
 * @author Daniel Huguenin             NUSP: 5118403
 * @author Antonio Rui Castro Junior   NUSP: 5984327
 * 
 * Esta classe foi feita com o intuito de testar todas as
 * funcionalidades da classe ListaCircular 
 */

public class Main {

	public static void main(String[] args) {

		ListaCircular<Integer> listaInt = new ListaCircular<Integer>();
		ListaCircular<String> listaString = new ListaCircular<String>();
		ListaCircular<Double> listaDouble = new ListaCircular<Double>();
		
		/*==================================Teste com inteiros ================================================*/
		System.out.println("\t\t Testando lista circular de inteiros \n");
		
		/*Insercao no tail da lista*/
		listaInt.Insere(46);
		listaInt.Insere(37);
		listaInt.Insere(25);
		listaInt.Insere(5);
		listaInt.Insere(5);
		listaInt.Insere(5);
		System.out.println("Insercao no fim: " + listaInt.ToString() + "\n");
		
		/*Insercao apos a ocorrencia do primeiro paramentro*/
		listaInt.Insere(10, 5);
		listaInt.Insere(50, 46);
		listaInt.Insere(70, 30);
		listaInt.Insere(100, 10);
		System.out.println("Insercao apos primeira ocorrencia: " +listaInt.ToString() + "\n");
		
		listaInt.Remove(70);
		listaInt.Remove(37);
		listaInt.Remove(46);
		System.out.println("Remove[70, 37, 46]: " + listaInt.ToString() + "\n");
		
		listaInt.RemoveTodos(5);
		System.out.println("Remove todas as ocorrencias de [5]: " +listaInt.ToString() + "\n");
		
		System.out.println("Numero de elementos da lista: " + listaInt.Tamanho() + "\n");
		
		/*==================================Teste com String ================================================*/
		System.out.println("\t\t Testando lista circular de string \n");
		
		/*Insercao no tail da lista*/
		listaString.Insere("Hirata");
		listaString.Insere("Gubi");
		listaString.Insere("Ernesto");
		listaString.Insere("Mandel");
		listaString.Insere("Ana Cristina");
		listaString.Insere("Fabio Kon");
		listaString.Insere("Carlinhos");
		System.out.println("Insercao no fim: " + listaString.ToString() + "\n");
		
		/*Insercao apos a ocorrencia do primeiro paramentro*/
		listaString.Insere("Nami","Hirata");
		listaString.Insere("Hirata","Setzer");
		listaString.Insere("Gerosa","Coelho");
		System.out.println("Insercao apos primeira ocorrencia: " +listaString.ToString() + "\n");
		
		listaString.Remove("Gerosa");
		listaString.Remove("Fabio Kon");
		listaString.Remove("Mandel");
		System.out.println("Remove[Gerosa,Fabio Kon,Mandel]: " + listaString.ToString() + "\n");
		
		listaString.RemoveTodos("Hirata");
		System.out.println("Remove todas as ocorrencias de [Hirata]: " +listaString.ToString() + "\n");
		
		System.out.println("Numero de elementos da lista: " + listaString.Tamanho() + "\n");
		
		
		/*==================================Teste com double ================================================*/
		System.out.println("\t\t Testando lista circular de double \n");
		
		/*Insercao no tail da lista*/
		listaDouble.Insere(46.745);
		listaDouble.Insere(37.9384);
		listaDouble.Insere(5.342);
		listaDouble.Insere(25.384);
		listaDouble.Insere(5.342);
		listaDouble.Insere(5.342);
		System.out.println("Insercao no fim: " + listaDouble.ToString() + "\n");
		
		/*Insercao apos a ocorrencia do primeiro paramentro*/
		listaDouble.Insere(10.2343, 5.342);
		listaDouble.Insere(50.356, 46.745);
		listaDouble.Insere(70.01, 30.4);
		listaDouble.Insere(100.123456789, 10.2343);
		System.out.println("Insercao apos primeira ocorrencia: " +listaDouble.ToString() + "\n");
		
		listaDouble.Remove(70.01);
		listaDouble.Remove(37.9384);
		listaDouble.Remove(46.745);
		System.out.println("Remove[70.01, 37.9384, 46.745]: " + listaDouble.ToString() + "\n");
		
		listaDouble.RemoveTodos(5.342);
		System.out.println("Remove todas as ocorrencias de [5.342]: " +listaDouble.ToString() + "\n");
		
		System.out.println("Numero de elementos da lista: " + listaDouble.Tamanho() + "\n");
		
	}

}
