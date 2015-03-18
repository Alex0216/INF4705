package com.inf4705;

import java.util.ArrayList;
import java.util.Comparator;

/**
 * Created by Alexandre on 3/17/2015.
 */
public class Vorace {

    public static void main(String[] args) {

        String file = args[0];
        ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);

        blocs.stream().flatMap(b -> b.getAllOrientation().stream()).sorted(new SurfaceComparator()).forEach(s -> System.out.println(s.Surface()));
    }

    /**
     * Comparator pour trier en ordre decroissant de surface
     */
    public static class SurfaceComparator implements Comparator<Bloc> {
        @Override
        public int compare(Bloc a, Bloc b) {
            return Integer.compare(b.Surface(), a.Surface());
        }
    }


}
