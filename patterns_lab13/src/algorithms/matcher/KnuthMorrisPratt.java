package algorithms.matcher;

import algorithms.Matcher;

import java.util.ArrayList;
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
        int q = 0;

        int[] prefixes = computePrefixFunction(p);

        for (int i = 0; i < n; i++) {

            while (q > 0 && p[q] != t[i-1]) {
                q = prefixes[q];
            }

            if (p[q] == t[i]) {
                q++;
            }

            if (q == m) {
                offsets.add(i-m);
                q = prefixes[q];
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
        int k = 0;

        int[] prefixes = new int[m];
        prefixes[0] = 0;

        for (int q = 1; q < m; q++) {
            while (k > 0 && pattern[k+1] != pattern[q]) {
                k = prefixes[k];
            }

            if (pattern[k+1] == pattern[q]) {
                k++;
            }

            prefixes[q] = k;
        }

        for (int prefix : prefixes) {
            System.out.print(prefix + ", ");
        }

        return prefixes;
    }
}
