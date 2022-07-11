/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package controlador;

import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import modelo.Cultivo;
import modelo.Parcela;
import modelo.Soja;
import modelo.TipoCultivo;
import modelo.Trigo;
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
    
    // Atributos del juego
    private int dinero = 50;
    private int experiencia = 0;
    private int nivel = 1;
    
    private IVista vista;
    private ArrayList<Parcela> parcelas = new ArrayList<>();
    private ArrayList<Cultivo> cultivos = new ArrayList<>();
    

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
    public ArrayList<Parcela> getParcelas(){
        return this.parcelas;
    }
    
    public ArrayList<Cultivo> getCultivos(){
        return this.cultivos;
    }
    

    //-------------------------------------------------
    // Funcionalidades
    //-------------------------------------------------

    public boolean comprar(Parcela parcela){
        int dineroRestante = this.dinero - Parcela.PRECIO;
        boolean exito = dineroRestante >= 0;
        if(exito){
            this.dinero = dineroRestante;
            this.experiencia += Parcela.EXPERIENCIA;
            subirNivel();
            
            // ----
            // EXAMEN
            
            // TODO Actualizar parcelas disponibles
            parcelas.add(new Parcela());
            // TODO Actualizar Vista del Juego
            vista.actualizarVista();
            
            // FIN DE EXAMEN
            // ----
        }
        return exito;
    }
    
    public boolean producir(Parcela parcela, TipoCultivo tipo){
        boolean exito = parcela.puedeProducir();
        
        if (exito){ //¿Puede producir?
            Cultivo cultivo = getCultivoDisponible(tipo);
            
            // ----
            // EXAMEN
            //TODO Obtener la duracion del cultivo 
            int duracionCultivo = 1;
            switch(tipo){
                case TRIGO:  
                    // ----
                    // EXAMEN
                    duracionCultivo = Trigo.DURACION;
                    // FIN DE EXAMEN
                    // ----
                break;
                case SOJA:  
                    // ----
                    // EXAMEN
                     duracionCultivo = Soja.DURACION;
                    // FIN DE EXAMEN
                    // ----
                break;
            }
            // FIN DE EXAMEN
            // ----
            
            exito = cultivo != null;
            
            if(exito){
                // ----
                // EXAMEN
                
                // TODO Dar la orden de producir al productor
                parcela.producir(cultivo);
                // TODO Actualizar cultivos disponibles
                cultivos.add(cultivo);
                // TODO Actualizar Vista del Juego
                vista.actualizarVista();;
                // FIN DE EXAMEN
                // ----
                
                //------------------------------------
                //Esperar tiempo de cultivo
                //------------------------------------
                Timer timer = new Timer();
                timer.schedule(new TimerTask() {
                    @Override
                    public void run () {
                        //recolectar
                        recolectar(parcela, cultivo);
                        
                        //cancelar el timer
                        timer.cancel();
                    }
                }, 
                        duracionCultivo * 1000
                );

            }
        }
        
        return exito;
    }
    
    public boolean vender(TipoCultivo tipo){
        Cultivo cultivo = getCultivoDisponible(tipo);
        boolean exito = cultivo != null;
        
        if(exito){
            //cobrar
            switch(tipo){
                case TRIGO:  
                    // ----
                    // EXAMEN
                    this.dinero += Trigo.PRECIO_VENTA;  //.PRECIO_VENTA; 
                    // FIN DE EXAMEN
                    // ----
                break;
                case SOJA:  
                    // ----
                    // EXAMEN
                    this.dinero += Soja.PRECIO_VENTA; //.PRECIO_VENTA; 
                    // FIN DE EXAMEN
                    // ----
                break;
            }
            
            // ----
            // EXAMEN

            //Actualizar cultivos disponibles tras la venta
            cultivos.remove(cultivo);
            //Actualizar Vista del Juego
            vista.actualizarVista();
            
            // FIN DE EXAMEN
            // ----
        }
        
        return exito;
    }
    
    private void recolectar(Parcela parcela, Cultivo cultivo){
        parcela.recolectar(cultivo);

        // ----
        // EXAMEN
        
        // recompensar experiencia del cultivo recolectado
        this.experiencia += cultivo.getExperienciaRecolecta();
        // FIN DE EXAMEN
        // ----
        
        subirNivel();

        //Actualizar cultivos disponibles tras la recolecta
        for(int i=0; i<Parcela.CAPACIDAD; i++){
            Cultivo nuevo = null;
            switch(cultivo.getTipo()){
                case TRIGO: 
                    // ----
                    // EXAMEN
                    // crea un nuevo cultivo de trigo
                    cultivo = new Trigo();
                    // FIN DE EXAMEN
                    // ----
                    break;
                case SOJA: 
                    // ----
                    // EXAMEN
                    
                    // crea un nuevo cultivo de soja
                    cultivo = new Soja();
                    // FIN DE EXAMEN
                    // ----
                break;
            }

 		
            if(nuevo != null){
               // ----
               // EXAMEN
               // añadir el cultivo a la lista de disponibles
               cultivos.add(cultivo);
               // FIN DE EXAMEN
               // ----
            }
        }

        this.vista.actualizarVista();
    }
    
    
    
    private Cultivo getCultivoDisponible(TipoCultivo tipo){
        Cultivo cultivo = null;
   
        //obtener un cultivo de la lista de disponibles, segun el tipo
        for(Cultivo c : this.cultivos){
            if(c.getTipo() == tipo){
                cultivo = c;
                break;
            }
        }

        return cultivo;
    }
    
    
    public int getCultivosDisponiblesDeUnTipo(TipoCultivo tipo){
        int disponibles = 0;
        
        // Recorrer los cultivos disponibles y contabilizarlos
        for(Cultivo cultivo : this.cultivos){
            if(cultivo.getTipo() == tipo){
                disponibles++;
            }
        }

        
        return disponibles;
    }
    
    public boolean subirNivel(){
        int progresoActual = getProgresoActual();
        boolean sube = this.experiencia >= progresoActual;
        if(sube){
           this.experiencia -= progresoActual;
           this.nivel ++;
        }
        return sube;
    }
    
    public void start(IVista vista, ArrayList<Parcela> parcelas,
            ArrayList<Cultivo> cultivos) {
        this.vista = vista;
        this.cultivos = cultivos;
        this.parcelas = parcelas;
        
        
        this.vista.inicializarVista();
        this.vista.actualizarVista();
        this.vista.mostrarVista();
    }
    
    public void finish (int i) {
        System.exit(i);
    }
    
}
