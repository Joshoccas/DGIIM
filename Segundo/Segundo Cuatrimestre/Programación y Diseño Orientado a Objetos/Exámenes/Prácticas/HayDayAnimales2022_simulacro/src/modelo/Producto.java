/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author Profe
 */
public abstract class Producto {
    //-------------------------------------------------
    //Atributos
    //-------------------------------------------------
    private String icono;
    private int duracionProduccion;
    private int experienciaRecolecta;
    private int precioVenta;

    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Producto(String icono, int duracionProduccion, int experienciaRecolecta, int precioVenta){
        this.icono = icono;
        this.duracionProduccion = duracionProduccion;
        this.experienciaRecolecta = experienciaRecolecta;
        this.precioVenta = precioVenta;
    }

    public Producto() {
        this.icono = "";
        this.duracionProduccion = 1;
        this.experienciaRecolecta = 1;
        this.precioVenta = 1;
    }
    
    
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------
    public String getIcono() {
        return icono;
    }

    public int getDuracionProduccion() {
        return duracionProduccion;
    }

    public int getExperienciaRecolecta() {
        return experienciaRecolecta;
    }

    public int getPrecioVenta() {
        return precioVenta;
    }

    public void setIcono(String icono) {
        this.icono = icono;
    }

    public void setDuracionProduccion(int duracionProduccion) {
        this.duracionProduccion = duracionProduccion;
    }

    public void setExperienciaRecolecta(int experienciaRecolecta) {
        this.experienciaRecolecta = experienciaRecolecta;
    }

    public void setPrecioVenta(int precioVenta) {
        this.precioVenta = precioVenta;
    }
    

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
    public abstract void enProduccion();
    
    
}
