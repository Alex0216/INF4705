package com.inf4705;

import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * Created by Alexandre on 3/17/2015.
 */
public class Vorace {

    public static void main(String[] args) throws java.io.IOException{

        FileWriter writer = new FileWriter("../vorace.csv");


        for(String file : new File("./").list()){
            ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
            long startTime = System.nanoTime();
            List<Bloc> ensemble = blocs.stream().flatMap(b -> b.getAllOrientation().stream()).sorted(new SurfaceRatioComparator()).collect(Collectors.toList());
            ArrayList<Bloc> solution = new ArrayList<>();
            solution.add(ensemble.remove(0));
            for (Bloc b : ensemble) {
                if (solution.get(solution.size() - 1).canStack(b))
                    solution.add(b);
            }
            long duration = System.nanoTime() - startTime;

            int hauteur = solution.stream().collect(Collectors.summingInt(b -> b.Hauteur));
            writer.append(file + ";");
            writer.append(Integer.toString(hauteur) + ";");
            writer.append(Long.toString(duration));
            writer.write(System.lineSeparator());

        }
        writer.close();
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
