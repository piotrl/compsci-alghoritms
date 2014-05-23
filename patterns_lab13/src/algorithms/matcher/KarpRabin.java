package algorithms.matcher;

import algorithms.Matcher;

import java.util.ArrayList;
import java.util.List;

public class KarpRabin implements Matcher {
    private static final int r = 256; // ASCII symbols number
    private static final int q = 9551;// a large prime number

    private String pattern;
    private long startTime;
    private long stopTime;


    public KarpRabin(String pattern) {
        this.pattern = pattern;
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

    @Override
    public List<Integer> match(String text) {
        startTime = System.currentTimeMillis();
        List<Integer> offsets = new ArrayList<Integer>();

        int n = text.length();
        int m = pattern.length();

        long hp = hash(pattern);
        long ht = hash(text.substring(0, m));

        for (int offset = 0; offset < n - m; offset++) {

            if (hp == ht) {
                if (text.substring(offset, offset + m).equals(pattern)) {
                    offsets.add(offset);
                }
            }

            ht = hash(text.substring(offset+1, offset+m+1));
        }

        stopTime = System.currentTimeMillis();
        return offsets;
    }

    private long hash(String s) {
        int hx;

        hx = 0;
        for (char c : s.toCharArray()) {
            hx = 3 * hx + c;
        }

        return hx;
    }

    private int fast_power_mod(int a, int b, int m) {
        int result = 1;
        long x = a%m;

        for (int i = 1; i <= b; i<<=1) {
            x %= m;

            if ((b & i) != 0) {
                result *= x;
                result %= m;
            }

            x *= x;
        }

        return result % m;
    }
}
