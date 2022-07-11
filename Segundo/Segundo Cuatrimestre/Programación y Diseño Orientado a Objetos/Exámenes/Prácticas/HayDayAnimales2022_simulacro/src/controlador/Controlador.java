/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package controlador;

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import modelo.ProductoAnimal;
import modelo.Animal;
import modelo.Leche;
import modelo.TipoProductoAnimal;
import modelo.Huevo;
import vista.IVista;

/**
 *
 * @author Profe
 * 
 * Patron: Singleton
 */
public class Controlador {
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    public static final Controlador instancia = new Controlador();
    private static final int[] PROGRESO = {27, 7, 14, 30, 50, 220, 370, 490, 790};
    
    private int dinero = 10;
    private int experiencia = 0;
    private int nivel = 1;
    private int piensoGallinaDisponible  = 10;
    private int piensoVacaDisponible  = 10;

    
    private IVista vista;
    private ArrayList<Animal> animales = new ArrayList<>();
    private ArrayList<ProductoAnimal> productos = new ArrayList<>();
    
    

    //-------------------------------------------------
    // Constructor
    //-------------------------------------------------
    private Controlador(){}
    
    //-------------------------------------------------
    // Getters & Setters
    //-------------------------------------------------
    public int getProgresoActual(){
        return PROGRESO[nivel-1];
    }
    public int getDinero() {
        return dinero;
    }

    public int getExperiencia() {
        return experiencia;
    }

    public int getNivel() {
        return nivel;
    }
    
    public int getPiensoGallinaDisponible() {
        return piensoGallinaDisponible;
    }
    public int getPiensoVacaDisponible() {
        return piensoVacaDisponible;
    }
    
    public ArrayList<Animal> getAnimales(){
        return this.animales;
    }
    
    public ArrayList<ProductoAnimal> getProductos(){
        return this.productos;
    }
    
    
    //-------------------------------------------------
    // Funciones privadas
    //-------------------------------------------------
    
    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------
    public boolean subirNivel(){
        int progresoActual = getProgresoActual();
        boolean sube = this.experiencia >= progresoActual;
        if(sube){
           this.experiencia -= progresoActual;
           this.nivel ++;
        }
        return sube;
    }
    
    public boolean comprar(Animal animal){
        int dineroRestante = this.dinero - animal.getPrecio();
        
        boolean exito = dineroRestante >= 0;
        if(exito){
            this.dinero = dineroRestante;

            //Actualizar productores disponibles
            this.animales.add(animal);
            
            //Actualizar Vista del Juego
            this.vista.actualizarVista();
        }
        return exito;
    }
    
    public boolean producir(Animal animal, TipoProductoAnimal tipo){
        boolean exito = animal.puedeProducir();
        
        if (exito){ //¿Puede producir?
            
                //dar la orden de producir al productor
                animal.producir();
                
                int duracion = 0;
                
                switch(animal.getTipo()){
                    case VACA: 
                        this.piensoVacaDisponible -= animal.getPienso();
                        duracion = Leche.DURACION;
                        break;
                    default: 
                        this.piensoGallinaDisponible -= animal.getPienso();
                        duracion = Huevo.DURACION;
                        break;
                }

                //Actualizar Vista del Juego
                this.vista.actualizarVista();
                
                //------------------------------------
                //Esperar tiempo de cultivo
                //------------------------------------
                Timer timer = new Timer();
                timer.schedule(new TimerTask() {
                    @Override
                    public void run () {
                        //recolectar
                        recolectar(animal);
                        
                        //cancelar el tiemr
                        timer.cancel();
                    }
                }, duracion * 1000);

        }
        
        return exito;
    }
    
    private void recolectar(Animal animal){
        ArrayList<ProductoAnimal> recolecta =  animal.recolectar();
        
        //Actualizar experiencia
        for(ProductoAnimal pa : recolecta){
            experiencia += pa.getExperienciaRecolecta();
            productos.add(pa); //Actualizar productos disponibles tras la recolecta
        }
        subirNivel();

        //Actualizar Vista del Juego
        vista.actualizarVista();
    }
    
    public boolean vender(TipoProductoAnimal tipo){
        ProductoAnimal producto = getProductoDisponible(tipo);
        boolean exito = producto != null;
        
        if(exito){
            //cobrar
            switch(tipo){
                case HUEVO:  this.dinero += Huevo.PRECIO_VENTA; break;
                case LECHE:  this.dinero += Leche.PRECIO_VENTA; break;
            }
            
            //actualizar cultivos disponebles tras la venta
            this.productos.remove(producto);
            
            //Actualizar Vista del Juego
            this.vista.actualizarVista();
        }
        
        return exito;
    }
    
    private ProductoAnimal getProductoDisponible(TipoProductoAnimal tipo){
        ProductoAnimal producto = null;
        
        //obtener un cultivo de la lista de disponibles, segun el tipo
        for(ProductoAnimal c : this.productos){
            if(c.getTipo() == tipo){
                producto = c;
                break;
            }
        }

        return producto;
    }
    
    public void start(IVista vista, ArrayList<Animal> parcelas,
            ArrayList<ProductoAnimal> cultivos) {
        this.vista = vista;
        this.productos = cultivos;
        this.animales = parcelas;
        
        
        this.vista.inicializarVista();
        this.vista.actualizarVista();
        this.vista.mostrarVista();
    }
    
    public void finish (int i) {
        System.exit(i);
    }
    
    public int getProductosDisponiblesDeUnTipo(TipoProductoAnimal tipo){
        int disponibles = 0;
        for(ProductoAnimal p : this.productos){
            if(p.getTipo() == tipo){
                disponibles++;
            }
        }
        return disponibles;
    }
    
}
