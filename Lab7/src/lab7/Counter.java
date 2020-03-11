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
public class Counter {
    int count = 0;
    
    
    /*
    This sync specifier below was not actually needed I was consistently getting 100?
    */
    public synchronized void add (int value){
        this.count += value;
        try{
            Thread.sleep(10);
        }   catch(InterruptedException ex){
            System.out.println("Should not get here! " + ex );
        }
    }
    
    
}
