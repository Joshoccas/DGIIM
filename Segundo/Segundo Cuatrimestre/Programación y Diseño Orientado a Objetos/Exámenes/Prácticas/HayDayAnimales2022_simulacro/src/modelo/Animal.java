/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.util.ArrayList;

/**
 *
 * @author Profe
 */
public class Animal {
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    private ArrayList<ProductoAnimal> produccion = new ArrayList<>();
    private TipoAnimal tipo;
    private int capacidadProduccion = 1;
    private int pienso = 1;
    private int precio = 1;


    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------

    public Animal(TipoAnimal t, int cp, int pi, int precio){
        this.tipo = t;
        this.capacidadProduccion = cp;
        this.pienso = pi;
        this.precio = precio;
    }
    
    

    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------
    
    public TipoAnimal getTipo() {    
        return tipo;
    }

    public void setTipo(TipoAnimal tipo) {
        this.tipo = tipo;
    }

    public ArrayList<ProductoAnimal> getProduccion() {
        return produccion;
    }

    public int getCapacidadProduccion() {
        return capacidadProduccion;
    }

    public int getPienso() {
        return pienso;
    }

    public void setProduccion(ArrayList<ProductoAnimal> produccion) {
        this.produccion = produccion;
    }

    public void setCapacidadProduccion(int capacidadProduccion) {
        this.capacidadProduccion = capacidadProduccion;
    }

    public void setPienso(int pienso) {
        this.pienso = pienso;
    }
    
    
    public int getPrecio() {
        return precio;
    }
    
    public void setPrecio(int precio) {
        this.precio = precio;
    }
    

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
    public boolean puedeProducir(){
        return this.produccion.size() < this.capacidadProduccion;
    }
    
    public void producir(){
        if(puedeProducir()){
            for(int i=0; i<this.capacidadProduccion; i++){
                switch(tipo){
                    case VACA: this.produccion.add(new Leche()); 
                    break;
                    default:
                        this.produccion.add(new Huevo()); 
                    break;
                }
            }
        }
    }
    
    public ArrayList<ProductoAnimal> recolectar(){
        ArrayList<ProductoAnimal> resultado = new ArrayList<>(this.produccion);
        this.produccion.removeAll(this.produccion);
        return resultado;
    }   
    
    
    public boolean estaProduciendo(){
        return this.produccion != null && this.produccion.size()>0;
    }
}
