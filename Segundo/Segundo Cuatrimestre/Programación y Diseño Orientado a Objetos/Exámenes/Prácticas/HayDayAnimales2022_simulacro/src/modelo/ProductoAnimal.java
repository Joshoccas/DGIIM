/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author Profe
 */
public abstract class ProductoAnimal extends Producto{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    private TipoProductoAnimal tipo;
    private int calidad;
    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------

    public ProductoAnimal(TipoProductoAnimal tipo, int calidad, String icono, int duracionProduccion, int experienciaRecolecta, int precioVenta) {
        super(icono, duracionProduccion, experienciaRecolecta, precioVenta);
        this.tipo = tipo;
        this.calidad = calidad;
    }
    public ProductoAnimal(ProductoAnimal p){
        super(p.getIcono(), p.getDuracionProduccion(), p.getExperienciaRecolecta(), p.getPrecioVenta());
        this.tipo = p.getTipo();
        this.calidad = p.getCalidad();
    }
    
    
    
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------
    public TipoProductoAnimal getTipo(){
        return this.tipo;
    }

    public int getCalidad() {
        return calidad;
    }
    
    public void setTipo(TipoProductoAnimal tipo) {
        this.tipo = tipo;
    }

    public void setCalidad(int calidad) {
        this.calidad = calidad;
    }
    
    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------

   
}
