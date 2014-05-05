package net.piotrl;

public class Main {

    public static void main(String[] args) {
	// write your code here

        Set[] Z = new Set[10];

        Z[0] = Set.make(0);
        Z[1] = Set.make(1);
        Z[2] = Set.make(2);
        Z[3] = Set.make(3);
        Z[4] = Set.make(4);
        Z[5] = Set.make(5);
        Z[6] = Set.make(6);
        Z[7] = Set.make(7);
        Z[8] = Set.make(8);
        Z[9] = Set.make(9);

        Z[0].union(Z[1]);
        Z[0].union(Z[3]);
        Z[0].union(Z[3]);
        Z[2].union(Z[3]);
        Z[4].union(Z[5]);
        Z[6].union(Z[7]);


        for (Set set : Z) {
            System.out.println(set);
        }
    }
}
