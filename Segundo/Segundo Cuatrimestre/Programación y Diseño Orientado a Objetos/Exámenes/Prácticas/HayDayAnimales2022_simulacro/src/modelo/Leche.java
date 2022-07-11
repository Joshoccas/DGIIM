/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author Profe
 */
public class Leche extends ProductoAnimal{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final String ICONO = "/img/leche40.png";
    public static final int DURACION = 5;
    public static final int EXPERIENCIA = 2;
    public static final int PRECIO_VENTA = 3;
    public static final int CALIDAD = 10;   
 
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public Leche(){
        super(TipoProductoAnimal.LECHE, CALIDAD, ICONO, DURACION, EXPERIENCIA, PRECIO_VENTA);
    }
    
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------    

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------

    @Override
    public void enProduccion() {
        System.out.println("Produciendo Leche");
    }
}
