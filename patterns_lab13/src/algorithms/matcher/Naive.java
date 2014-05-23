package algorithms.matcher;

import algorithms.Matcher;

import java.util.ArrayList;
import java.util.List;

public class Naive implements Matcher {

    private String pattern;
    private long stopTime;
    private long startTime;

    public Naive(String pattern) {
        this.pattern = pattern;
    }

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

    @Override
    public List<Integer> match(String text) {
        startTime = System.currentTimeMillis();
        int n = text.length();
        int m = pattern.length();

        List<Integer> offsets = new ArrayList<Integer>();

        char[] textChars = text.toCharArray();
        char[] patternChars = pattern.toCharArray();

        for (int offset = 0; offset < n - m; offset++) {
            int i = 0;
            while (i < m && textChars[offset + i] == patternChars[i] ) {
                i++;
            }

            if (i == m) {
                // pattern are true
                offsets.add(offset); // extend result
            }
        }

        stopTime = System.currentTimeMillis();
        return offsets;
    }
}
