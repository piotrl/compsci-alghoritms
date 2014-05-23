
import algorithms.Matcher;
import algorithms.matcher.KarpRabin;
import algorithms.matcher.KnuthMorrisPratt;
import algorithms.matcher.Naive;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class PatternsTest {

    private static final String textFileName = "textSample.txt";
    private static final String patternFileName = "patternSample.txt";

    public static void main(String[] args) throws IOException {
        Matcher matcher;

        String pattern = getText(patternFileName);
        String textSample = getText(textFileName);

        matcher = new Naive(pattern);
        System.out.println("Naive String Matcher:");
        printOutput(matcher, textSample);

        matcher = new KarpRabin(pattern);
        System.out.println("Karp-Rabin Matcher:");
        printOutput(matcher, textSample);

        matcher = new KnuthMorrisPratt("ABACABAB");
        System.out.println("Knuth-Morris-Pratt Matcher:");
        printOutput(matcher, "babaaaaacbabaABACABABabaac");

    }

    private static void printOutput(Matcher matcher, String textSample) {
        List<Integer> offsets;
        offsets = matcher.match(textSample);

        System.out.println(offsets);
        System.out.println(matcher.getRunTime() + "ms");
    }

    private static String getText(String fileName) throws IOException {
        List<String> lines;
        lines = readStrings(fileName);
        StringBuilder pattern = new StringBuilder("");

        for (String line : lines) {
            pattern.append(line);
        }

        return pattern.toString();
    }

    private static List<String> readStrings(String fileName) throws IOException {
        Path textFilePath = Paths.get(PatternsTest.class.getResource(fileName).getPath());
        return Files.readAllLines(textFilePath, StandardCharsets.UTF_8);
    }

}
