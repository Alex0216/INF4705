package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Created by Alexandre on 3/17/2015.
 */
public class Vorace {

    public static void main(String[] args) throws java.io.IOException{

        if(args[0].compareTo("-f") == 0)
        {
            String fichier = args[1];
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(fichier);
            long startTime = System.nanoTime();
            ArrayList<Bloc> solution = Vorace(blocs);
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
        FileWriter writer = new FileWriter("../vorace.csv");

        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            ArrayList<Bloc> solution = Vorace(blocs);
            long duration = System.nanoTime() - startTime;

            int hauteur = solution.stream().collect(Collectors.summingInt(b -> b.Hauteur));
            writer.append(file + ";");
            writer.append(Integer.toString(hauteur) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());

        }
        writer.close();
    }

    private static ArrayList<Bloc> Vorace(ArrayList<Bloc> blocs) {
        List<Bloc> ensemble = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).sorted(new SurfaceRatioComparator()).collect(Collectors.toList());
        ArrayList<Bloc> solution = new ArrayList<>();
        solution.add(ensemble.remove(0));
        for (Bloc b : ensemble) {
            if (solution.get(solution.size() - 1).canStack(b))
                solution.add(b);
        }
        return solution;
    }

    /**
     * Comparator pour trier en ordre decroissant de surface
     */
    public static class SurfaceRatioComparator implements Comparator<Bloc> {
        @Override
        public int compare(Bloc a, Bloc b) {

            return Float.compare(b.RatioMagique(), a.RatioMagique());
        }
    }


}
