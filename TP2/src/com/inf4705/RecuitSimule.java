package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.lang.reflect.GenericArrayType;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

/**
 * Created by Alexandre on 3/24/2015.
 */
public class RecuitSimule {

    public static void main(String[] args) throws java.io.IOException{

        FileWriter writer = new FileWriter("../dynamique.csv");


        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            //ConstruireTourRS
            //Etendre l'ensemble de depart avec les trois orientation
            List<Bloc> B = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).collect(Collectors.toList());

            double T = 5;
            double P = 16;
            double alpha = 1.5;
            ArrayList<Bloc> solutionInitial = GenereSolutionInitial(B);
            ArrayList<Bloc> Smeilleur = new ArrayList<>(solutionInitial);



            long duration = System.nanoTime() - startTime;

            writer.append(file + ";");
            writer.append(Integer.toString(2) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());
        }
        writer.close();
    }

    public static ArrayList<Bloc> voisin(List<Bloc> S, List<Bloc> B){

    }

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

    public static boolean CritereMetropolis(double delta, double T){
        if(delta > 0){
            return true;
        }
        Random r = new Random();
        if(Math.exp(delta/T) >= r.nextDouble()){
            return true;
        }
        return false;
    }

}
