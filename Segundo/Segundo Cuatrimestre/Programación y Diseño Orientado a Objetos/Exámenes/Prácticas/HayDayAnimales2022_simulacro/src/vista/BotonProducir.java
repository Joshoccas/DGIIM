/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package vista;

import controlador.Controlador;
import modelo.TipoProductoAnimal;
import java.awt.event.ActionEvent;


/**
 *
 * @author Profe
 */
public class BotonProducir extends javax.swing.JButton{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    private VistaAnimal parcelaView;
    private TipoProductoAnimal tipoProductoAnimal;
    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public BotonProducir(VistaAnimal pv, TipoProductoAnimal tipoProductoAnimal, String rutaIcono){
        this.parcelaView = pv;
        this.tipoProductoAnimal = tipoProductoAnimal;
        this.setText("Producir");
        this.setIcon(new javax.swing.ImageIcon(getClass().getResource(rutaIcono)));
        
        this.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCultivarActionPerformed(evt);
            }
        });
    }
    
    //-------------------------------------------------
    // Getters && Setters
    //-------------------------------------------------
    public VistaAnimal getParcelaView(){
        return this.parcelaView;
    }
    public TipoProductoAnimal getTipoCultivo(){
        return this.tipoProductoAnimal;
    }
    
    //-------------------------------------------------
    // Funciones
    //-------------------------------------------------    
    private void btnCultivarActionPerformed(ActionEvent evt) {
        Controlador.instancia.producir(this.parcelaView.getAnimal(), this.tipoProductoAnimal);
    }
    
}
