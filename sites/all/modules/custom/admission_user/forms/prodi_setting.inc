<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function prodi_setting_form($form, $form_state){
   $prodi_array = node_load_multiple(array(), array('type' => 'departement'));
   if(isset($prodi_array)){
       $prodi_urut = array();
       foreach($prodi_array as $prodi){
           $prodi_urut[$prodi->nid] = $prodi->field_departement_priority['und'][0]['value'];
       }
       asort($prodi_urut);
       
       $prodi_options = array();
       foreach($prodi_urut as $nid => $value){
           $prodi = node_load($nid);
           $prodi_options[$prodi->nid] = $prodi->field_departement_name['und'][0]['value'];
       }
   }
    $form['title'] = array(
        '#type' => 'markup',
        '#markup' => t('<h4>Konfigurasi Program Studi berdasarkan Jurusan Sekolah</h4>'),
    );
    
    $default_prodi = variable_get('default_prodi');
    $form['prodi_default'] = array(
        '#type' => 'checkbox',
        '#title' => 'Default (Jika diceklist maka semua program studi -> untuk semua jurusan)',
        '#description' => t('Semua jurusan boleh mengambil program studi apapun'),
        //'#options' => $prodi_options,
        '#default_value' => $default_prodi,
    );
    
    $ipa = variable_get('ipa');
    $form['prodi_ipa'] = array(
        '#type' => 'checkboxes',
        '#title' => 'IPA:',
        '#options' => $prodi_options,
        '#default_value' => array_values($ipa),
    );
    
    $ips = variable_get('ips');
    $form['prodi_ips'] = array(
        '#type' => 'checkboxes',
        '#title' => 'IPS:',
        '#options' => $prodi_options,
        '#default_value' => array_values($ips),
    );
    
    $bahasa = variable_get('bahasa');
     $form['prodi_bahasa'] = array(
        '#type' => 'checkboxes',
        '#title' => 'Bahasa:',
        '#options' => $prodi_options,
        '#default_value' => array_values($bahasa),
    );
     
     $smk = variable_get('smk');
     $form['prodi_lain'] = array(
        '#type' => 'checkboxes',
        '#title' => 'Lainnya:',
        '#options' => $prodi_options,
        '#default_value' => array_values($smk),
    );
    
//     $form['submit'] = array(
//         '#type' => 'submit',
//         '#value' => t('Simpan Konfigurasi'),
//     );
     
    return system_settings_form($form);
//     return $form;
}

//function prodi_setting_form_submit($form, &$form_state){dpm($form_state,'state');
//    variable_set('prodi_setting',$form_state['values']);
//}