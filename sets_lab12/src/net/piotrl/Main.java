package net.piotrl;

import javax.sound.midi.Soundbank;
import java.util.*;

public class Main {

    public static void main(String[] args) {

        // -------------------------------
        // G = (V, E, w)

        List<int[]> edges = new ArrayList<int[]>();
        // v = edge[0]
        // u = edge[1]
        // weight = edge[2]

        edges.add(new int[] {1, 2, 1});
        edges.add(new int[] {1, 3, 20});
        edges.add(new int[] {2, 3, 0});
        edges.add(new int[] {4, 3, 3});
        edges.add(new int[] {4, 1, 2});
        edges.add(new int[] {4, 2, 5});
        edges.add(new int[] {5, 2, 5});


        List<int[]> tree = kruskal(edges);

        int i = 0;
        for (int[] ints : tree) {
            i++;
            System.out.println(ints[0] + " - " + ints[1]);
        }


    }

    private static List<int[]> kruskal(List<int[]> edges) {
        List<int[]> A = new ArrayList<int[]>();

        Map<Integer, Set> V = createGraphValues(edges);

        // sort edges
        Collections.sort(edges, new Comparator<int[]>() {
            @Override
            public int compare(int[] e1, int[] e2) {
                return e1[2] - e2[2];   // e1[2] - weight of e1
            }
        });

        for (int[] edge : edges) {
            Set v = V.get(edge[0]);
            Set u = V.get(edge[1]);

            if (Set.find(u) != Set.find(v) ) {
                A.add(edge);
                u.union(v);
            }
        }

        System.out.println("|V| = " + V.values().size());
        System.out.println("|A| = " + A.size());

        return A;
    }

    private static Map<Integer, Set> createGraphValues(List<int[]> E) {
        Map<Integer, Set> V = new HashMap<Integer, Set>();

        for (int[] edge : E) {
            int v = edge[0];
            int u = edge[1];

            if (!V.containsKey(v)) {
                V.put(v, Set.make(v));
            }

            if (!V.containsKey(u)) {
                V.put(u, Set.make(u));
            }
        }

        return V;
    }
}
