package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Created by Alexandre on 3/22/2015.
 */
public class Dynamique {

    static int solution[];

    public static void main(String[] args) throws java.io.IOException{

        FileWriter writer = new FileWriter("../dynamique.csv");


        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            List<Bloc> ensemble = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).sorted(new SurfaceComparator()).collect(Collectors.toList());
            solution  = new int[ensemble.size()];
            for(int i = 0; i < ensemble.size(); ++i)
                solution[i] = 0;
            int hauteurMax = 0;

            for(int i = 0; i < ensemble.size(); ++i){
                hauteurMax = Math.max(hauteurMax, calculeHauteur(ensemble, i));
            }

            long duration = System.nanoTime() - startTime;

            writer.append(file + ";");
            writer.append(Integer.toString(hauteurMax) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());
            System.out.println(hauteurMax);
        }
        writer.close();
    }

    public static int calculeHauteur(List<Bloc> blocs, int currentIndex)
    {
        if(solution[currentIndex] != 0)
            return solution[currentIndex];

        ArrayList<Integer> hauteur = new ArrayList<>();

        for(int i = 0; i < currentIndex; ++i){
            if(blocs.get(i).canStack(blocs.get(currentIndex)))
            hauteur.add(calculeHauteur(blocs, i));
        }

        solution[currentIndex] = blocs.get(currentIndex).Hauteur;
        if(hauteur.size() > 0)
            solution[currentIndex] += Collections.max(hauteur);
        return solution[currentIndex];
    }

    /**
     * Comparator pour trier en ordre decroissant de surface
     */
    public static class SurfaceComparator implements Comparator<Bloc> {
        @Override
        public int compare(Bloc a, Bloc b) {

            return Float.compare(b.Surface(), a.Surface());
        }
    }
}
