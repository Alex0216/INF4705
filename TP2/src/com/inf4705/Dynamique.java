package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

/**
 * Created by Alexandre on 3/22/2015.
 */
public class Dynamique {

    static int solution[][];

    public static void main(String[] args) throws java.io.IOException{
        if(args[0].compareTo("-f") == 0)
        {
            String fichier = args[1];
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(fichier);
            long startTime = System.nanoTime();
            List<Bloc> solution = Dynamique(blocs);
            long duration = System.nanoTime() - startTime;
            long milli = TimeUnit.NANOSECONDS.toMillis(duration);
            int Hauteur = solution.stream().mapToInt(Bloc::getHauteur).sum();
            System.out.println("Temps : " + milli + "ms, Nb blocs: " + solution.size() + ", Hauteur: " + Hauteur);
            if(args.length >= 3 &&  args[2].compareTo("-p") == 0)
            {
                for(int i = solution.size()-1; i >=0; --i)
                {
                    System.out.println(solution.get(i));
                }
            }
        }
        //Test();
    }

    private static List<Bloc> GetTour(int hauteur, List<Bloc> blocs)
    {
        int index = 0;
        while(solution[index][0] != hauteur)
            index++;

        List<Bloc> tours = new ArrayList<>();
        tours.add(blocs.get(index));
        while(solution[index][1] != index){
            index = solution[index][1];
            tours.add(blocs.get(index));
        }

        return tours;
    }

    private static void Test() throws IOException {
        FileWriter writer = new FileWriter("../dynamique.csv");


        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            List<Bloc> solution = Dynamique(blocs);

            long duration = System.nanoTime() - startTime;
            int hauteur = solution.stream().mapToInt(Bloc::getHauteur).sum();
            writer.append(file + ";");
            writer.append(Integer.toString(hauteur) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());
            System.out.println(hauteur);
        }
        writer.close();
    }

    private static List<Bloc> Dynamique(ArrayList<Bloc> blocs) {
        List<Bloc> ensemble = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).sorted(new SurfaceComparator()).collect(Collectors.toList());
        solution  = new int[ensemble.size()][2];
        for(int i = 0; i < ensemble.size(); ++i)
            for(int j = 0; j < solution[i].length; ++j)
                solution[i][j] = 0;

        int hauteurMax = 0;

        for(int i = 0; i < ensemble.size(); ++i){
            hauteurMax = Math.max(hauteurMax, calculeHauteur(ensemble, i));
        }

        return GetTour(hauteurMax, ensemble);
    }

    public static int calculeHauteur(List<Bloc> blocs, int currentIndex)
    {
        if(solution[currentIndex][0] != 0)
            return solution[currentIndex][0];

        int maxHauteur = 0;
        int maxIndex = currentIndex;
        for(int i = 0; i < currentIndex; ++i){
            if(blocs.get(i).canStack(blocs.get(currentIndex))) {
                int tmp = calculeHauteur(blocs, i);
                if ( tmp > maxHauteur)
                {
                    maxHauteur = tmp;
                    maxIndex = i;
                }
            }
        }

        solution[currentIndex][0] = blocs.get(currentIndex).Hauteur;

        if(maxHauteur > 0) {
            solution[currentIndex][0] += maxHauteur;
            solution[currentIndex][1] = maxIndex;
        }
        else
        {
            solution[currentIndex][1] = currentIndex;
        }
        return solution[currentIndex][0];
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
