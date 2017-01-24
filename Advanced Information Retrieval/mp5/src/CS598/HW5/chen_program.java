package CS598.HW5;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.lang.Math;

class CS598HW5{
    public static void main(String[] args){
      System.out.println("Put the value for K (integer)");
      Scanner scan1 = new Scanner(System.in);
      kNum = scan1.nextInt();
      System.out.println("Put the value for Lambda (double)");
      Scanner scan2 = new Scanner(System.in);
      lambda = scan2.nextDouble();

      file = "dblp-small.txt";
      listOfDocWordCounts = new ArrayList<HashMap<String, Integer>>();
      listOfDocWordIndex = new ArrayList<HashMap<String, Integer>>();
      listOfDocIndexWord = new ArrayList<HashMap<Integer, String>>();
      wordCounts = new HashMap<String, Integer>();
      wordIndex = new HashMap<String, Integer>();
      indexWord = new HashMap<Integer, String>();
      num_lines = 0;
      num_words = 0;
      num_distinctWords = 0;
      longestDocDistinctWords = 0;
      //kNum = 20;
      //lambda = 0.9;
      epsilon = 0.0001;
      delta = 0;
      numLines_wordCounts_wordIndex_docWords();
      docTopicDist = new Double [num_lines][kNum];
      topicWordDist = new Double [kNum][num_distinctWords];
      backgroundDist = new Double [num_distinctWords];
      updateMatrix = new Double [num_lines][kNum][longestDocDistinctWords];
      initialize_stuff();

      System.out.println(String.format("Lambda value is: %f", lambda));
      System.out.println(String.format("K value is: %d", kNum));
      lastTimeLog = log_likelihood ();
      update_variables();
      thisTimeLog = log_likelihood ();
      delta = (lastTimeLog - thisTimeLog)/lastTimeLog;
      System.out.println(delta);

      int num_iteration = 0;
      while(delta>epsilon && num_iteration<100){
        lastTimeLog = thisTimeLog;
        update_variables();
        thisTimeLog = log_likelihood ();
        delta = (lastTimeLog - thisTimeLog)/lastTimeLog;
        System.out.println(delta);
        num_iteration++;
      }

      for(int i=0;i<kNum;i++){
        System.out.println(" #################### Another Topic ####################### : ");
        double upperbound = 2;
        for (int iter=0;iter<10;iter++){
          double max = 0;
          Integer index = 0;
          for (int j=0;j<num_distinctWords;j++){
            if (topicWordDist[i][j] > max && topicWordDist[i][j] < upperbound ){
              max = topicWordDist[i][j];
              index = j;
            }
          }
          System.out.println(indexWord.get(index));
          upperbound = max;
        }
      }

    }

    private static void numLines_wordCounts_wordIndex_docWords (){
      try{
        BufferedReader br = new BufferedReader(new FileReader(file));
        String line;
        while((line = br.readLine()) != null){
          num_lines ++;
          String delims = " +";
          String[] words = line.split(delims);
          HashMap<String, Integer> doc_map = new HashMap<String, Integer>();
          HashMap<String, Integer> word_index = new HashMap<String, Integer>();
          HashMap<Integer, String> index_word = new HashMap<Integer, String>();
          num_words += words.length;

          Integer docDistinctWord = 0;
          for (int i=0; i< words.length;i++){
            Integer countWord= 0;
            if((countWord = wordCounts.get(words[i]))==null){
                countWord = 0;
                wordIndex.put(words[i],num_distinctWords);
                indexWord.put(num_distinctWords,words[i]);
                num_distinctWords ++;
            }
            wordCounts.put(words[i],countWord+1);

            Integer doc_countWord= 0;
            if((doc_countWord = doc_map.get(words[i]))==null){
                doc_countWord = 0;
                word_index.put(words[i],docDistinctWord);
                index_word.put(docDistinctWord,words[i]);
                docDistinctWord++;
            }
            doc_map.put(words[i],doc_countWord+1);
          }
          longestDocDistinctWords = (docDistinctWord>longestDocDistinctWords ? docDistinctWord :longestDocDistinctWords);
          listOfDocWordCounts.add(doc_map);
          listOfDocWordIndex.add(word_index);
          listOfDocIndexWord.add(index_word);

        }
/*
        System.out.println(wordCounts.size());
        System.out.println(wordIndex.size());
        System.out.println(num_distinctWords);
        System.out.println(listOfDocWordCounts.size());
        System.out.println(listOfDocWordIndex.size());
        System.out.println(listOfDocIndexWord.size());
        System.out.println(num_lines);
        System.out.println(longestDocDistinctWords);
*/
      } catch(IOException e){
         e.printStackTrace();
      }
    }

    // initialize p(w|D), p(z=k|\pi_d) and p(w|\theta_k)
    private static void initialize_stuff (){
      for (int i=0;i<num_distinctWords;i++){
        backgroundDist[i] = (double)wordCounts.get(indexWord.get(i))/num_words;
      }

      for (int i=0;i<num_lines;i++){
        double total_value = 0;
        for (int j=0;j<kNum;j++){
          docTopicDist[i][j] = Math.random();
          total_value+=docTopicDist[i][j];
        }
        for (int j=0;j<kNum;j++){
          docTopicDist[i][j] = docTopicDist[i][j]/total_value;
        }
      }

      for (int i=0;i<kNum;i++){
        double total_value = 0;
        for (int j=0;j<num_distinctWords;j++){
          topicWordDist[i][j] = Math.random();
          total_value += topicWordDist[i][j];
        }
        for (int j=0;j<num_distinctWords;j++){
          topicWordDist[i][j] = topicWordDist[i][j]/total_value;
        }
      }
    }

    private static double log_likelihood () {
      Iterator<HashMap<String, Integer>> docWordIter = listOfDocWordCounts.iterator();
      Iterator<HashMap<Integer, String>> indexWordIter = listOfDocIndexWord.iterator();

      double likelihood = 0.0;
      Integer doc_counter = 0;
      while (docWordIter.hasNext()){
        HashMap<String, Integer> doc_wordCounts = docWordIter.next();
        HashMap<Integer, String> doc_indexWord = indexWordIter.next();
        Integer word_counter = 0 ;
        String word = null;
        while((word = doc_indexWord.get(word_counter))!=null){
          double k_sum =0.0;
          Integer index_glob = wordIndex.get(word);
          for (int i=0;i<kNum;i++){
            k_sum+=docTopicDist[doc_counter][i]*topicWordDist[i][index_glob];
          }
          likelihood += doc_wordCounts.get(word)*(Math.log(lambda*backgroundDist[index_glob]+(1-lambda)*k_sum)/Math.log(2));

          for (int k=0;k<kNum;k++){
            updateMatrix[doc_counter][k][word_counter] = (1-lambda)*docTopicDist[doc_counter][k]*topicWordDist[k][index_glob]/(lambda*backgroundDist[index_glob]+(1-lambda)*k_sum);
          }

          word_counter++;
        }
        doc_counter++;
      }
      System.out.println(likelihood);
      return likelihood;
    }

    private static void update_variables() {

      Iterator<HashMap<String, Integer>> docWordIter = listOfDocWordCounts.iterator();
      Iterator<HashMap<Integer, String>> indexWordIter = listOfDocIndexWord.iterator();
      Integer doc_counter = 0;
      double [][] interim_topicword = new double [kNum][num_distinctWords];

      while (docWordIter.hasNext()){
        HashMap<String, Integer> doc_wordCounts = docWordIter.next();
        HashMap<Integer, String> doc_indexWord = indexWordIter.next();
        double [] interim_doctopic = new double [kNum];
        Integer word_counter = 0 ;
        String word = null;
        while((word = doc_indexWord.get(word_counter))!=null){
          Integer index_glob = wordIndex.get(word);
          Integer interim_docwordcount = doc_wordCounts.get(word);
          for (int j=0;j<kNum;j++){
            interim_doctopic[j] += interim_docwordcount*updateMatrix[doc_counter][j][word_counter];
            interim_topicword[j][index_glob] += interim_docwordcount*updateMatrix[doc_counter][j][word_counter];
          }
          word_counter++;
        }

        double total_value = 0.0;
        for (int j=0;j<kNum;j++){
          total_value += interim_doctopic[j];
        }
        for (int j=0;j<kNum;j++){
          docTopicDist[doc_counter][j] = interim_doctopic[j]/total_value;
        }
        doc_counter++;
      }

      for (int j=0;j<kNum;j++){
        double total_value = 0.0;
        for (int m=0;m<num_distinctWords;m++){
          total_value+=interim_topicword[j][m];
        }
        for (int m=0;m<num_distinctWords;m++){
          topicWordDist[j][m] = interim_topicword[j][m]/total_value;
        }
      }

    }

    private static String file; // the name of the file
    private static int num_words; // total number of words in the collection
    private static int num_lines; // total number of documents in the collection
    private static int num_distinctWords; // number of distinct word in the collection
    private static ArrayList<HashMap<String, Integer>> listOfDocWordCounts; //
    private static ArrayList<HashMap<String, Integer>> listOfDocWordIndex; // local word and index
    private static ArrayList<HashMap<Integer, String>> listOfDocIndexWord; // local index and word
    private static int longestDocDistinctWords; // longest number of distinct words in one document
    private static HashMap<String, Integer> wordCounts ; // word and its counts in whole collection
    private static HashMap<String, Integer> wordIndex ;  // word and index in the whole collection matrix
    private static HashMap<Integer, String> indexWord ;  // index and its word in the whole colleciton matrix
    private static Double[][] docTopicDist;  //doc topic dist, D*K
    private static Double[][] topicWordDist; // topic word dist K*num_distinctWords
    private static Double[]   backgroundDist; // background dist , num_distinctWords*1
    private static Double[][][] updateMatrix; // update matrix, D*K*longestDocDistinctWords
    private static int kNum;
    private static double lambda;
    private static double lastTimeLog;
    private static double thisTimeLog;
    private static double delta;
    private static double epsilon;
}
