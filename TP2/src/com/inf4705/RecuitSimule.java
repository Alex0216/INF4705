package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.GenericArrayType;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

/**
 * Created by Alexandre on 3/24/2015.
 */
public class RecuitSimule {

    public static void main(String[] args) throws java.io.IOException{
        if(args[0].compareTo("-f") == 0)
        {
            String fichier = args[1];
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(fichier);
            long startTime = System.nanoTime();
            ArrayList<Bloc> solution = Recuit(blocs);
            long duration = System.nanoTime() - startTime;
            long milli = TimeUnit.NANOSECONDS.toMillis(duration);

            int hauteur = solution.stream().mapToInt(Bloc::getHauteur).sum();
            System.out.println("Temps : " + milli + "ms, Nb blocs: " + solution.size() + ", Hauteur: " + hauteur);
            if(args.length >= 3 &&  args[2].compareTo("-p") == 0)
            {
                for(Bloc b : solution)
                {
                    System.out.println(b);
                }
            }
        }


        //Test();
    }

    private static void Test() throws IOException {
        FileWriter writer = new FileWriter("../recuit.csv");


        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            //ConstruireTourRS
            //Etendre l'ensemble de depart avec les trois orientation
            ArrayList<Bloc> Smeilleur = Recuit(blocs);

            int hauteurFinal = Hauteur(Smeilleur);

            long duration = System.nanoTime() - startTime;

            writer.append(file + ";");
            writer.append(Integer.toString(hauteurFinal) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());
        }
        writer.close();
    }

    private static ArrayList<Bloc> Recuit(ArrayList<Bloc> blocs) {
        List<Bloc> B = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).collect(Collectors.toList());

        double T = 100;
        double theta = T;
        double P = 50;
        int Kmax = 50;
        double alpha = 0.8;
        ArrayList<Bloc> S = GenereSolutionInitial(B);
        ArrayList<Bloc> Smeilleur = new ArrayList<>(S);

        for(int i = 0; i < Kmax; ++i){
            for(int j = 1; j <= P; ++j){
                ArrayList<Bloc> Snouveau = voisin(S, B);
                int delta = Hauteur(Snouveau) - Hauteur(S);
                if(CritereMetropolis(delta, theta )){
                    S = Snouveau;
                    if(Hauteur(S) - Hauteur(Smeilleur) > 0){
                        Smeilleur = S;
                    }
                }
            }
            //metttre a jour la temperature
            theta = theta * alpha;
        }
        return Smeilleur;
    }

    /**
     * Insere un bloc choisie aleatoirement dans la solution
     * @param S
     * @param B
     * @return
     */
    public static ArrayList<Bloc> voisin(List<Bloc> S, List<Bloc> B){
        //Choisir le bloc aleatoirement
        Random rand = new Random(System.currentTimeMillis());
        Bloc bloc = B.get(rand.nextInt(B.size()));
        ArrayList<Bloc> voisin = new ArrayList<>();
        //inserer le bloc des que possible
        int i = 0;
        while(i < S.size() && S.get(i).canStack(bloc)) {
            voisin.add(S.get(i));
            i++;
        }
        voisin.add(bloc);

        //ajouter les bloc qui peuvent etre mis par dessus le nouveau bloc

        while(i < S.size() && !bloc.canStack(S.get(i))){
            i++;
        }
        while(i < S.size())
            voisin.add(S.get(i++));

        return voisin;
    }

    public static int Hauteur(List<Bloc> blocs){
        return blocs.stream().mapToInt(Bloc::getHauteur).sum();
    }

    /**
     * Creer une solution initial simple
     * @param B
     * @return
     */
    public static ArrayList<Bloc> GenereSolutionInitial(List<Bloc> B)
    {
        B.sort(new Dynamique.SurfaceComparator());
        ArrayList<Bloc> S = new ArrayList<>();
        Bloc blocReceveur = null;
        for(int i = 0; i < B.size(); ++i){
            Bloc nouveauBloc = B.get(i);
            if(S.isEmpty() || blocReceveur.canStack(nouveauBloc)){
                S.add(nouveauBloc);
                blocReceveur = nouveauBloc;
            }
        }
        return S;
    }

    public static boolean CritereMetropolis(int delta, double T){
        if(delta > 0){
            return true;
        }
        Random r = new Random();
        double x = delta/T;
        if(Math.exp(delta/T) >= r.nextDouble()){
            return true;
        }
        return false;
    }

}
