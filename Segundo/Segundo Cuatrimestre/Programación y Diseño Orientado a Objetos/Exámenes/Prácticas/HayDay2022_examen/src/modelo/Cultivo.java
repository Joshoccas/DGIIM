/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;


public abstract class Cultivo extends Producto {
    
    // ----
    // EXAMEN

    private int riego;
    private TipoCultivo tipo;

    public Cultivo() {
    }

    public Cultivo(int riego, TipoCultivo tipo) {
        this.riego = riego;
        this.tipo = tipo;
    }

    public Cultivo(int riego, TipoCultivo tipo, String icono, int duracionProduccion, int experienciaRecolecta, int precioVenta) {
        super(icono, duracionProduccion, experienciaRecolecta, precioVenta);
        this.riego = riego;
        this.tipo = tipo;
    }

    

    public int getRiego() {
        return riego;
    }

    public void setRiego(int riego) {
        this.riego = riego;
    }
    
    
    // TODO ...
    
    public TipoCultivo getTipo(){
        return tipo;
    }
    
    // FIN DE EXAMEN
    // ----
}
