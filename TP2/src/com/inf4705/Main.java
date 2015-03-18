package com.inf4705;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        String file = args[0];
        ArrayList<Bloc> blocs = Bloc.ReadTestFile(file);
        blocs.forEach(s->System.out.println(s));
    }
}
