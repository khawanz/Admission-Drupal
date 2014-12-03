<?php

//not used.
function setting_ujian_form(){
    
//    $batas_dokumen_default = is_null(variable_get('batas_dokumen'))?date('Y-m-d'):variable_get('batas_dokumen');
//    $form['batas_dokumen'] = array(
//        //'#title' => t('Batas Penyerahan Dokumen:'),
//        '#type' => 'date_popup',
//        //'#description' => t('Please select the date of booking'),
//        '#required' => TRUE,
//        '#date_format' => 'd M Y',
//        '#date_year_range' => '-1:+1',    
//        '#default_value' => $batas_dokumen_default,
//        '#date_label_position' => 'within',      
//        '#prefix' => '<div class="container-inline"><b>Batas Penyerahan Dokumen:</b>',
//        '#suffix' => '</div>',
//    );
//    
//    $batas_pembayaran_default = is_null(variable_get('batas_pembayaran'))?date('Y-m-d'):variable_get('batas_pembayaran');
//    $form['batas_pembayaran'] = array(
//        //'#title' => t('Batas Penyerahan Dokumen:'),
//        '#type' => 'date_popup',
//        //'#description' => t('Please select the date of booking'),
//        '#required' => TRUE,
//        '#date_format' => 'd M Y',
//        '#date_year_range' => '-1:+1',    
//        '#default_value' => $batas_pembayaran_default,
//        '#date_label_position' => 'within',      
//        '#prefix' => '<div class="container-inline"><b>Batas Pembayaran Biaya Pendaftaran USM:</b>',
//        '#suffix' => '</div>',
//    );
    
    $form['materi'] = array(
        '#title' => t('Materi Test'),
        '#description' => t('Dapat memanfaatkan kode html untuk mengatur tampilan.'),      
        '#type' => 'textarea',
        '#default_value' => variable_get('materi'),
    );
    
    $form['perlengkapan'] = array(
        '#title' => t('Perlengkapan Test'),
        '#description' => t("Dapat memanfaatkan kode html untuk mengatur tampilan."),
        '#type' => 'textarea',
        '#default_value' => variable_get('perlengkapan'),
    );
    
    return system_settings_form($form);
}
