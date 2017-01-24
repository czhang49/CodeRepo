package CS598.HW2;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Map;
import java.util.Arrays;
import java.lang.Math;

class CS598HW2{
    public static void main(String[] args){
      String file = "cacm.trec.filtered.txt";
      BufferedReader br = null;
      HashMap<Pair,Integer> pairCounts = new HashMap<Pair,Integer> ();
      HashMap<String,Integer> wordCounts = new HashMap<String,Integer> ();
      HashSet<String> wordRecords = new HashSet<String>();
      //HashSet<String> wholeWordRecords = new HashSet<String>();
      HashSet<Pair> pairSet = new HashSet<Pair>();
      Integer wholeCollection = 0;

      try{
          // This needs to be at the operation folder path
          br = new BufferedReader(new FileReader(file));
          String line;
          while((line = br.readLine()) != null){
              wholeCollection++;
              String delims = "[ ]+";
              String[] words = line.split(delims);
              for (int i=0; i< words.length;i++){
                  wordRecords.add(words[i]);
                  //wholeWordRecords.add(words[i]);
                  Integer countWord= 0;
                  if((countWord = wordCounts.get(words[i]))==null){
                      countWord = 0;
                  }
                  wordCounts.put(words[i],countWord+1);
              }
              LinkedList<String> wordList = new LinkedList<String> ();
              Iterator<String> wordIterator = wordRecords.iterator();
              while (wordIterator.hasNext()){
                  wordList.add(wordIterator.next());
              }
              /*for (String s : wordRecords){
                  wordList.add(s);
              }*/
              // because the wordlist size keep decreasing for each iteration
              while (wordList.size()>1){
                  String first = wordList.poll();

                  ListIterator<String> listIter= wordList.listIterator(0);
                  while(listIter.hasNext()){
                    Pair newpair = new Pair (first,listIter.next());
                    Integer count;
                    if((count = pairCounts.get(newpair))==null){
                        count = 0;
                    }
                    pairSet.add(newpair);
                    pairCounts.put(newpair,count+1);
                  }
              }
              wordRecords.clear();
          }
          br.close();
          //System.out.println("The total number of words is " + wordRecords.size() + "\n");
       } catch(IOException e){
          e.printStackTrace();
       }

       /*for ( Map.Entry<Pair,Integer> entry : pairCounts.entrySet()){
           System.out.println("The pair is: "+entry.getKey().wholePair()+" and value is : "+ entry.getValue()+"\n");
       }*/
       Integer[] valueArray = pairCounts.values().toArray(new Integer[pairCounts.size()]);
       /*System.out.println("Before sorting");
       for (Integer i:valueArray)
         System.out.println(i);
         */
       Arrays.sort(valueArray);
       /*System.out.println("After sorting");
       for (Integer i:valueArray)
         System.out.println(i);
         */
       HashSet<Integer> valueSet = new HashSet<Integer> ();
       for (int i=0;i<valueArray.length;i++){
         valueSet.add(valueArray[i]);
       }
       Integer[] newvalueArray = valueSet.toArray(new Integer[valueSet.size()]);

       Integer printNum = 30;
       Integer counter = 0;
       Boolean finishedPrinting = false;
       for (int i=newvalueArray.length-1; i>=0;i--){
         Integer valueTofind =newvalueArray[i];
         for (Map.Entry<Pair,Integer> entry:pairCounts.entrySet()){
           if (entry.getValue().equals(valueTofind)){
             System.out.println(entry.getKey().getfirst()+" "+entry.getKey().getsecond()+" "+entry.getValue());
             counter++;
             if (counter.equals(printNum))
               finishedPrinting = true;
           }
           if (finishedPrinting)
             break;
         }
         if (finishedPrinting)
             break;
       }

       //////////////////
       ////////////////
       calc_mutual(pairSet,wordCounts,pairCounts,wholeCollection,file);

       calc_mutual_programming(pairSet,wordCounts,pairCounts,wholeCollection,file);
       ///////////////////
       ///////////////////
       //test_pair();
    }

    public static void calc_mutual_programming(HashSet<Pair> pairSet,HashMap<String,Integer> wordCounts,HashMap<Pair,Integer> pairCounts,Integer wholeCollection,String file){

      HashMap<Pair,Double>  pairInfo = new HashMap<Pair,Double>();
      BufferedReader br = null;

      /*LinkedList<String> wholeWordList = new LinkedList<String> ();
      Iterator<String> wholeWordIterator = wholeWordRecords.iterator();
      while (wholeWordIterator.hasNext()){
          wholeWordList.add(wholeWordIterator.next());
      }*/
      /*for (String s : wordRecords){
          wordList.add(s);
      }*/
      // because the wordlist size keep decreasing for each iteration
      /*while (wholeWordList.size()>1){
          String first = wholeWordList.poll();
          ListIterator<String> listIter= wholeWordList.listIterator(0);
          while(listIter.hasNext()){
            String second = listIter.next();*/
            int iternum = 0;
          Iterator<Pair> pairIter= pairSet.iterator();
          Double[] informationMutual = new Double [10];
          for (int i=0;i<informationMutual.length;i++)
            informationMutual[i]=0.0;

          while(pairIter.hasNext()){
            iternum++;
            if (iternum%100000 ==0)
              System.out.println("Num Iteration is : " +iternum);
            //Pair newpair = new Pair (first,second);
            Pair newpair = pairIter.next();
            String first = newpair.getfirst();
            String second = newpair.getsecond();
            if ((!first.equals("programming") && !second.equals("programming")))
              continue;

            int first1=wordCounts.get(first);
            int second1=wordCounts.get(second);
            int first1second1=pairCounts.get(newpair);
            int first0second0= wholeCollection - first1-second1+first1second1;
            int first0second1=second1 - first1second1;
            int first1second0=first1- first1second1;


            /*try{

            br = new BufferedReader(new FileReader(file));
            String line;
            while((line = br.readLine()) != null){
               boolean containsFirst = line.contains(first);
               boolean containsSecond = line.contains(second);
               if (containsFirst)
                 first1++;
               if (containsSecond)
                 second1++;
               if (!containsFirst && !containsSecond)
                 first0second0++;
               if (!containsFirst && containsSecond)
                 first0second1++;
               if (containsFirst && !containsSecond)
                 first1second0++;
               if (containsFirst && containsSecond)
                 first1second1++;

                if ((first1!= (first1second0+first1second1))||(second1!= (first0second1+first1second1)))
                  System.out.println("The counting has a problem");
            }
            br.close();*/
            Double mutualInfo = calc_mutual_info(first1,second1,first0second0,first0second1,first1second0,first1second1,wholeCollection);

            if(pairInfo.get(newpair)!=null){
                System.out.println("The newpair already has a value, something is not right.");
            }
            for (int i=0;i<informationMutual.length;i++){
              if (mutualInfo>informationMutual[i]){
                informationMutual[i] = mutualInfo;
                break;
              }
            }
            pairInfo.put(newpair,mutualInfo);
          /*}catch(IOException e){
            e.printStackTrace();
          }*/
        }
      /*    }
    }*/

      /*for ( Map.Entry<Pair,Double> entry : pairInfo.entrySet()){
          System.out.println("The pair is: "+entry.getKey().wholePair()+" and value is : "+ entry.getValue()+"\n");
      }*/

      Double[] valueArrayold = pairInfo.values().toArray(new Double[pairInfo.size()]);
      /*System.out.println("Before sorting");
      for (Integer i:valueArray)
        System.out.println(i);
        */
      /*Double[] valueArray = new Double [valueArrayold.length];
      for (int i =0;i<valueArrayold.length;i++){
        valueArray[i]=valueArrayold[i]*1000;
      }
      Arrays.sort(valueArray);*/
      /*System.out.println("After sorting");
      for (Integer i:valueArray)
        System.out.println(i);
        */
      /*HashSet<Double> valueSet = new HashSet<Double> ();
      for (int i=0;i<valueArray.length;i++){
        valueSet.add(valueArray[i]);
      }
      Double[] newvalueArray = valueSet.toArray(new Double[valueSet.size()]);*/
      Double[] newvalueArray = informationMutual;

      Integer printNum = 10;
      Integer counter = 0;
      Boolean finishedPrinting = false;
      for (int i=newvalueArray.length-1; i>=0;i--){
        Double valueTofind =newvalueArray[i];
        for (Map.Entry<Pair,Double> entry:pairInfo.entrySet()){
          if (entry.getValue().equals(valueTofind)){
            System.out.println(entry.getKey().getfirst()+" "+entry.getKey().getsecond()+" "+entry.getValue());
            counter++;
            if (counter.equals(printNum))
              finishedPrinting = true;
          }
          if (finishedPrinting)
            break;
        }
        if (finishedPrinting)
            break;
      }

    }

    public static void calc_mutual(HashSet<Pair> pairSet,HashMap<String,Integer> wordCounts,HashMap<Pair,Integer> pairCounts,Integer wholeCollection,String file){

      HashMap<Pair,Double>  pairInfo = new HashMap<Pair,Double>();
      BufferedReader br = null;

      /*LinkedList<String> wholeWordList = new LinkedList<String> ();
      Iterator<String> wholeWordIterator = wholeWordRecords.iterator();
      while (wholeWordIterator.hasNext()){
          wholeWordList.add(wholeWordIterator.next());
      }*/
      /*for (String s : wordRecords){
          wordList.add(s);
      }*/
      // because the wordlist size keep decreasing for each iteration
      /*while (wholeWordList.size()>1){
          String first = wholeWordList.poll();
          ListIterator<String> listIter= wholeWordList.listIterator(0);
          while(listIter.hasNext()){
            String second = listIter.next();*/
            int iternum = 0;
          Iterator<Pair> pairIter= pairSet.iterator();
          Double[] informationMutual = new Double [10];
          for (int i=0;i<informationMutual.length;i++)
            informationMutual[i]=0.0;

          while(pairIter.hasNext()){
            iternum++;
            if (iternum%100000 ==0)
              System.out.println("Num Iteration is : " +iternum);
            //Pair newpair = new Pair (first,second);
            Pair newpair = pairIter.next();
            String first = newpair.getfirst();
            String second = newpair.getsecond();


            int first1=wordCounts.get(first);
            int second1=wordCounts.get(second);
            int first1second1=pairCounts.get(newpair);
            int first0second0= wholeCollection - first1-second1+first1second1;
            int first0second1=second1 - first1second1;
            int first1second0=first1- first1second1;


            /*try{

            br = new BufferedReader(new FileReader(file));
            String line;
            while((line = br.readLine()) != null){
               boolean containsFirst = line.contains(first);
               boolean containsSecond = line.contains(second);
               if (containsFirst)
                 first1++;
               if (containsSecond)
                 second1++;
               if (!containsFirst && !containsSecond)
                 first0second0++;
               if (!containsFirst && containsSecond)
                 first0second1++;
               if (containsFirst && !containsSecond)
                 first1second0++;
               if (containsFirst && containsSecond)
                 first1second1++;

                if ((first1!= (first1second0+first1second1))||(second1!= (first0second1+first1second1)))
                  System.out.println("The counting has a problem");
            }
            br.close();*/
            Double mutualInfo = calc_mutual_info(first1,second1,first0second0,first0second1,first1second0,first1second1,wholeCollection);

            if(pairInfo.get(newpair)!=null){
                System.out.println("The newpair already has a value, something is not right.");
            }
            for (int i=0;i<informationMutual.length;i++){
              if (mutualInfo>informationMutual[i]){
                informationMutual[i] = mutualInfo;
                break;
              }
            }
            pairInfo.put(newpair,mutualInfo);
          /*}catch(IOException e){
            e.printStackTrace();
          }*/
        }
      /*    }
    }*/

      /*for ( Map.Entry<Pair,Double> entry : pairInfo.entrySet()){
          System.out.println("The pair is: "+entry.getKey().wholePair()+" and value is : "+ entry.getValue()+"\n");
      }*/

      Double[] valueArrayold = pairInfo.values().toArray(new Double[pairInfo.size()]);
      /*System.out.println("Before sorting");
      for (Integer i:valueArray)
        System.out.println(i);
        */
      /*Double[] valueArray = new Double [valueArrayold.length];
      for (int i =0;i<valueArrayold.length;i++){
        valueArray[i]=valueArrayold[i]*1000;
      }
      Arrays.sort(valueArray);*/
      /*System.out.println("After sorting");
      for (Integer i:valueArray)
        System.out.println(i);
        */
      /*HashSet<Double> valueSet = new HashSet<Double> ();
      for (int i=0;i<valueArray.length;i++){
        valueSet.add(valueArray[i]);
      }
      Double[] newvalueArray = valueSet.toArray(new Double[valueSet.size()]);*/
      Double[] newvalueArray = informationMutual;

      Integer printNum = 10;
      Integer counter = 0;
      Boolean finishedPrinting = false;
      for (int i=newvalueArray.length-1; i>=0;i--){
        Double valueTofind =newvalueArray[i];
        for (Map.Entry<Pair,Double> entry:pairInfo.entrySet()){
          if (entry.getValue().equals(valueTofind)){
            System.out.println(entry.getKey().getfirst()+" "+entry.getKey().getsecond()+" "+entry.getValue());
            counter++;
            if (counter.equals(printNum))
              finishedPrinting = true;
          }
          if (finishedPrinting)
            break;
        }
        if (finishedPrinting)
            break;
      }

    }

    public static Double calc_mutual_info(int first1,int second1,int first0second0,int first0second1,int first1second0,int first1second1,int wholeCollection){

        Double pf0s0=((double)first0second0+0.25)/((double)wholeCollection+1);
        Double pf0s1=((double)first0second1+0.25)/((double)wholeCollection+1);
        Double pf1s0=((double)first1second0+0.25)/((double)wholeCollection+1);
        Double pf1s1=((double)first1second1+0.25)/((double)wholeCollection+1);
        Double pf1 = pf1s0+pf1s1;
        Double pf0 = pf0s0+pf0s1;
        Double ps1 = pf0s1+pf1s1;
        Double ps0 = pf0s0+pf1s0;

        Double mutualinfo = pf0s0*(Math.log(pf0s0/pf0/ps0)/Math.log(2))
                            +pf0s1*(Math.log(pf0s1/pf0/ps1)/Math.log(2))
                            +pf1s0*(Math.log(pf1s0/pf1/ps0)/Math.log(2))
                            +pf1s1*(Math.log(pf1s1/pf1/ps1)/Math.log(2));
        return mutualinfo;

    }

    public static void test_pair(){
        Pair pair1 = new Pair("string1","string2");
        Pair pair2 = new Pair("string1","string2");
        Pair pair3 = new Pair("string2","string1");
        Pair pair4 = new Pair("string3","string4");
        Pair pair5 = new Pair("string3","string5");
        Pair pair7 = new Pair("string5","string3");

        HashSet<Pair> pairRecords = new HashSet<Pair>();
        pairRecords.add(pair1);
        pairRecords.add(pair2);
        pairRecords.add(pair3);
        pairRecords.add(pair4);
        pairRecords.add(pair5);
        pairRecords.add(pair7);

        System.out.println("The correct size is 3, and the number of pairs in the hashset is " +pairRecords.size()+".\n");

    }


}
