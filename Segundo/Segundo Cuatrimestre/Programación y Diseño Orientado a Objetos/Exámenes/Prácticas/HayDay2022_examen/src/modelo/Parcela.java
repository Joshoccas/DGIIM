/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.util.ArrayList;



public class Parcela {
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final String ICONO = "/img/parcela.png"; 
    public static final int PRECIO = 15;
    public static final int MAX_CULTIVOS = 1;
    public static final int CAPACIDAD = 2;
    public static final int EXPERIENCIA = 1;

    // ----
    // EXAMEN


    // TODO a) Inicializa la relación entre Parcela y Cultivo.
    private ArrayList<Cultivo> cultivos = new ArrayList<>(); 


    // FIN DE EXAMEN
    // ----

    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Parcela(){
        cultivos = new ArrayList<>();
    }
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------
    public ArrayList<Cultivo> getCultivos() {    
        return cultivos;
    }

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
    public boolean puedeProducir(){
        // ----
        // EXAMEN
        
        return (cultivos.size() < Parcela.MAX_CULTIVOS);
        // FIN DE EXAMEN
        // ----
    }
    
    public void producir(Cultivo cultivo){
       // ----
       // EXAMEN
       if(puedeProducir()){
           cultivos.add(cultivo);
       }
       // FIN DE EXAMEN
       // ----
    }
    
    public void recolectar(Cultivo cultivo){
         // ----
        // EXAMEN
        for(Cultivo c: cultivos){
            if(c.getTipo() == cultivo.getTipo()){
                cultivos.remove(c);
                break;
            }
        }
       // FIN DE EXAMEN
       // ----
    }   
    
    public Cultivo getPrimerCultivo() {
        Cultivo cultivo = null;
        
        if(this.cultivos.size() > 0){
            cultivo = this.cultivos.get(0);
        }
        
        return cultivo;
    }
    
    public boolean estaCultivando(){
        return getPrimerCultivo() != null;
    }
    
    public boolean cultivandoTrigo(){
        return this.getPrimerCultivo().getTipo() == TipoCultivo.TRIGO;
    }
    public boolean cultivandoSoja(){
        return this.getPrimerCultivo().getTipo() == TipoCultivo.SOJA;
    }
}
