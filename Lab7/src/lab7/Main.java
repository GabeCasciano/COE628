/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab7;

/**
 *
 * @author gabriel
 */
public class Main {

    public static void main(String[] args) {
        Counter counter = new Counter();
        Thread threadA = new CounterThread(counter, 10);
        Thread threadB = new CounterThread(counter, 11);
        
        System.out.println("Starting A");
        threadA.start();
        
        System.out.println("Starting B");
        threadB.start();
        
        try{
            threadB.join();
            System.out.println("B Finished");
            
            threadA.join();
            System.out.println("A Finished");
            
        }   catch(InterruptedException ex){
            System.out.println("Should not get here! " + ex );
        }
        
        System.out.println("Counter: " + counter.count);
    }
    
}
