/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package genql;

import java.io.File;
import org.apache.commons.cli.BasicParser;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Options;

/**
 *
 * @author Amirhossein Aleyasen <aleyase2@illinois.edu>
 * created on Apr 2, 2016, 1:14:53 PM
 */
public class CLIRunner {

    private static boolean isEval = false;
    private static boolean isGen = false;

    private static String corpusDir;
    private static String outputFile;
    private static String groundTruthQueryFile;
    private static String generatedQueryFile;
    private static int qcount;
    private static int min_query_len;
    private static int max_query_len;

    public static void main(String[] args) {
        Options options = setupOptions();
        CommandLineParser parser = new BasicParser();
        try {
//            for (int i = 0; i < args.length; i++) {
//                System.out.println(args[i]);
//            }
            CommandLine line = parser.parse(options, args);
            if (line.hasOption('e')) {
                isEval = true;
            }
            if (line.hasOption('g')) {
                isGen = true;
            }
            if (line.hasOption('d')) {
                corpusDir = line.getOptionValue('d');
            }
            if (line.hasOption('n')) {
                qcount = Integer.parseInt(line.getOptionValue('n'));
            } else {
                qcount = 10;
            }
            if (line.hasOption('o')) {
                outputFile = line.getOptionValue('o');
            }
            if (line.hasOption('g')) {
                groundTruthQueryFile = line.getOptionValue('g');
            }
            if (line.hasOption('q')) {
                generatedQueryFile = line.getOptionValue('q');
            }
            if (line.hasOption('m')) {
                min_query_len = Integer.parseInt(line.getOptionValue('m'));
            } else {
                min_query_len = 2;
            }
            if (line.hasOption('x')) {
                max_query_len = Integer.parseInt(line.getOptionValue('x'));
            } else {
                max_query_len = 7;
            }
            if (line.hasOption('h')) {
                printHelpAndExit(options);
            }

            if (isGen) {
                MainApp.gen(corpusDir, outputFile, qcount, min_query_len, max_query_len);
            } else if (isEval) {
                final String intermediateResults = corpusDir + "/temp";
                new File(intermediateResults).mkdir();
                MainApp.eval(corpusDir, generatedQueryFile, groundTruthQueryFile, intermediateResults, min_query_len, max_query_len);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.err.println("Unexpected exception: " + ex.getMessage());
            System.exit(1);
        }
    }

    private static Options setupOptions() {
        Options options = new Options();
        options.addOption("g", "gen", false, "Generate search query log");
        options.addOption("e", "eval", false, "Evaluate generated queries based on a ground-truth query log");
        options.addOption("d", "dir", true, "The directory for the corpus");
        options.addOption("o", "output", true, "Output file for the generated queries");
        options.addOption("n", "count", true, "Numbers of queries to generate (default: 10)");
        options.addOption("t", "gtruth", true, "The ground-truth queries file (only for evaluation). Each line of the file contains a query");
        options.addOption("q", "query", true, "The generated queries file (only for evaluation)");
        options.addOption("m", "min", true, "Minimum query length (default: 2)");
        options.addOption("x", "max", true, "Maximum query length (default: 7)");

        options.addOption("h", "help", false, "help");

//        options.addOption("o", "output", true, "Output file/directory path");
//        options.addOption("o", "output", true, "Output file/directory path");
        return options;
    }

    private static void printHelpAndExit(Options options) {
        HelpFormatter formatter = new HelpFormatter();
        formatter.printHelp("genql.jar", options, true);
        System.exit(1);
    }

}
