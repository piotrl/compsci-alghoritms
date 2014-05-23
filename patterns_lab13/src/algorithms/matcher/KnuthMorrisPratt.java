package algorithms.matcher;

import algorithms.Matcher;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class KnuthMorrisPratt implements Matcher {

    private String pattern;
    private long startTime = 0;
    private long stopTime = 0;

    public KnuthMorrisPratt(String pattern) {
        this.pattern = pattern;
    }

    @Override
    public List<Integer> match(String text) {
        startTime = System.currentTimeMillis();
        List<Integer> offsets = new ArrayList<Integer>();
        char[] p = pattern.toCharArray();
        char[] t = text.toCharArray();

        int n = t.length;
        int m = p.length;
        int b = 0;

        int[] prefixes = computePrefixFunction(p);

        for (int i = 0; i < n; i++) {

            while (b > 0 && p[b] != t[i]) {
                b = prefixes[b];
            }

            if (p[b] == t[i]) {
                b++;
            }

            if (b == m) {
                offsets.add(i-m+1);
                b = prefixes[b];
            }
        }

        stopTime = System.currentTimeMillis();
        return offsets;
    }

    @Override
    public long getRunTime() {
        return stopTime - startTime;
    }

    @Override
    public String getPattern() {
        return pattern;
    }

    @Override
    public void setPattern(String pattern) {
        this.pattern = pattern;
    }

    private int[] computePrefixFunction(char[] pattern) {
        int m = pattern.length;

        int[] prefixes = new int[m+1];
        prefixes[0] = -1;
        int b = -1;


        for (int i = 1; i <= m; i++) {
            while (b > -1 && pattern[b] != pattern[i-1]) {
                b = prefixes[b];
            }

            prefixes[i] = ++b;
        }

//        prefixes = Arrays.copyOfRange(prefixes, 1, prefixes.length);

//        for (int prefix : prefixes) {
//            System.out.print(prefix + ", ");
//        }
//        System.out.println();
        return prefixes;
    }
}
