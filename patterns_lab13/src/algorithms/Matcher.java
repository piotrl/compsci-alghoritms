package algorithms;

import java.util.List;

public interface Matcher {
    List<Integer> match(String text);

    long getRunTime();

    String getPattern();

    void setPattern(String pattern);

}
