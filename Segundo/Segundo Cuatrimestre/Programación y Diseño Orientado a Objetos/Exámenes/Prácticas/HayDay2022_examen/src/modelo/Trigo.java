/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;


public class Trigo extends Cultivo {
    public static final String ICONO = "/img/trigo.png";
    public static final int PRECIO_VENTA = 2;
    public static final int EXPERIENCIA = 1;
    public static final int DURACION = 2;
    public static final int RIEGO = 10;
    
    // ----
    // EXAMEN


    // TODO ...
    
    public Trigo(){
        super(Trigo.RIEGO, TipoCultivo.TRIGO, Trigo.ICONO, Trigo.DURACION, Trigo.EXPERIENCIA, Trigo.PRECIO_VENTA);
    }
    
    @Override
    public void setRiego(int riego){
        if(riego <= Trigo.RIEGO){
            super.setRiego(riego);
        }
    }

    public void enProduccion(){
        System.out.println("Cultivando Trigo");
    }
    // FIN DE EXAMEN
    // ----
}
