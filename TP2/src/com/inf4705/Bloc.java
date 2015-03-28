package com.inf4705;

import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.reflect.Array;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.stream.Stream;

/**
 * Created by Alexandre on 3/17/2015.
 */
public class Bloc {

    public int Hauteur;
    public int Largeur;
    public int Profondeur;

    public Bloc(int h, int l, int p)
    {
        Hauteur = h;
        Largeur = Math.max(l,p);
        Profondeur = Math.min(l, p);
    }

    public ArrayList<Bloc> getAllOrientation()
    {
        ArrayList<Bloc> blocs = new ArrayList<>(3);
        blocs.add(new Bloc(Hauteur, Largeur, Profondeur ));
        blocs.add(new Bloc(Largeur, Hauteur, Profondeur));
        blocs.add(new Bloc(Profondeur, Hauteur, Largeur));

        return blocs;
    }

    public int getHauteur(){
        return Hauteur;
    }

    public Bloc getBestOrientation(){
        ArrayList<Bloc> blocs = getAllOrientation();
        blocs.sort(new Vorace.SurfaceRatioComparator());
        return blocs.get(0);
    }

    public int Surface()
    {
        return Largeur*Profondeur;
    }

    public float RatioMagique()
    {
        return ((float)Profondeur/(float)Largeur) * Surface();
    }

    public boolean canStack(Bloc up)
    {
        return Largeur > up.Largeur && Profondeur > up.Profondeur;
    }

    public String toString()
    {
        return "H:" + Hauteur + " L: " + Largeur + " P: " + Profondeur;
    }

    public static ArrayList<Bloc> ReadTestFile(String filename)
    {
        Path path = Paths.get(filename);
        String first = "";
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            first = br.readLine();
        }
        catch(Exception e){}
        int size = Integer.parseInt(first);
        final ArrayList<Bloc> list = new ArrayList<>(size);
        try(Stream<String> lines = Files.lines(path)){

            lines.skip(1).forEach(ligne -> {
                String[] split = ligne.split("\\s+");
                int h = Integer.parseInt(split[0]);
                int l = Integer.parseInt(split[1]);
                int p = Integer.parseInt(split[2]);
                list.add(new Bloc(h, l, p));
            });

        }catch (java.io.IOException e){

        }
        return list;
    }

}
