package CS598.HW2;


class Pair {

  public Pair(String first, String second){
    this.first = first;
    this.second = second;
  }

  public void printString(){
    System.out.println("The first string is : "+first+", the second string is : "+second +"\n");
  }

  public String getfirst(){
    return this.first;
  }

  public String getsecond(){
    return this.second;
  }

  public String wholePair(){
    return this.first+"+"+this.second;
  }
  //@Override
  public int hashCode(){
    return first.hashCode()+second.hashCode();
    //return 1;
  }

  //@Override
  public boolean equals(Object obj){
    if (obj == this)
      return true;
    if (!(obj instanceof Pair))
      return false;

    Pair other = (Pair) obj;
    return (exactEquals(other)||switchEquals(other));
  }

  private boolean exactEquals(Pair other){
      return (this.first.equals(other.getfirst()) && this.second.equals(other.getsecond()));
  }

  private boolean switchEquals(Pair other){
      return (this.first.equals(other.getsecond()) && this.second.equals(other.getfirst()));
  }

  private String first;
  private String second;

}
