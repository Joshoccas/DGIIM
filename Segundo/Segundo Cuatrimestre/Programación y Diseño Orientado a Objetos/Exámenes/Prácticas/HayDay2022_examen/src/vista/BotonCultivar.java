/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package vista;

import controlador.Controlador;
import modelo.TipoCultivo;
import java.awt.event.ActionEvent;


/**
 *
 * @author Profe
 */
public class BotonCultivar extends javax.swing.JButton{
    //-------------------------------------------------
    // Atributos
    //-------------------------------------------------
    private VistaParcela parcelaView;
    private TipoCultivo tipoCultivo;
    
    //-------------------------------------------------
    // Constructores
    //-------------------------------------------------
    public BotonCultivar(VistaParcela pv, TipoCultivo tipoCultivo, String rutaIcono){
        this.parcelaView = pv;
        this.tipoCultivo = tipoCultivo;
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
    public VistaParcela getParcelaView(){
        return this.parcelaView;
    }
    public TipoCultivo getTipoCultivo(){
        return this.tipoCultivo;
    }
    
    //-------------------------------------------------
    // Funciones
    //-------------------------------------------------    
    private void btnCultivarActionPerformed(ActionEvent evt) {
        Controlador.instancia.producir(this.parcelaView.getParcela(), this.tipoCultivo);
    }
    
}
