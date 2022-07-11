/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author Profe
 */
public class Huevo extends ProductoAnimal{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final String ICONO = "/img/huevo40.png";
    public static final int DURACION = 2;
    public static final int EXPERIENCIA = 1;
    public static final int PRECIO_VENTA = 2;
    public static final int CALIDAD = 30;   
 
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Huevo(){
        super(TipoProductoAnimal.HUEVO, CALIDAD, ICONO, DURACION, EXPERIENCIA, PRECIO_VENTA);
    }
    
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------    

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
     @Override
    public void enProduccion() {
        System.out.println("Produciendo Huevo");
    }

    @Override
    public void setCalidad(int calidad) {
        if(calidad >= CALIDAD){
            super.setCalidad(calidad); 
        }
    }
    
    
}
