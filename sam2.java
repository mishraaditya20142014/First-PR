import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
//creating a class
class sam2
{
    protected void finalize()
    {
        System.out.println("Coding!!");
    }
    public static void main(String[] args)
    {
        sam2 hacker=new sam2();
        hacker=null;
        System.gc();
    }
}
    
