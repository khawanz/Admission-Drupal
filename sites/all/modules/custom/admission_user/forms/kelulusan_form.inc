<?php

function kelulusan_form($form, &$form_state){
    
//   $form['filter'] = array(
//       '#title' => t('Filter'),
//        '#type' => 'fieldset',
//       '#collapsible' => TRUE,
//       '#collapsed' => empty($input_pembayaran)? FALSE:TRUE,
//    );
//   
//   $form['filter']['noreg'] = array(
//       '#title' => 'No.Registrasi:',
//       '#type' => 'textfield',
//       '#size' => 15
//   );
//   
//   $form['filter']['nama'] = array(
//       '#title' => 'Nama:',
//       '#type' => 'textfield',
//       '#size' => 60
//   );
//   
   $input = variable_get('kelulusan');
    
    $gelombang_default = empty($input['gelombang'])? 'all':$input['gelombang'];
    $form['filter']['gelombang'] = array(
       '#title' => 'Gelombang:',
       '#type' => 'select',
       '#options' => array(
           'all' => 'ALL',
           1 => '1',
           2 => '2',
           3 => '3',
           4 => '4',
       ),
        '#default_value' => $gelombang_default
   );
   
       $form['filter']['submit'] = array(
           '#type' => 'submit',
           '#value' => 'Filter'
       );
  
    $reg_array = node_load_multiple(array(), array('type' => 'registration'));
   
   if(isset($reg_array)){
        $form['kelulusan'] = array(
            '#tree' => TRUE,
          );
        
        $prodi_array = node_load_multiple(array(), array('type' => 'departement'));
        $prodi_options = array();
        foreach($prodi_array as $prodi_node){
            $prodi_options[$prodi_node->nid] = $prodi_node->title;
        }
        
        $result_table = FALSE;
        $i = 0;
       foreach($reg_array as $reg_nid => $reg_node){
           $user_id = $reg_node->field_reg_candidate['und'][0]['target_id'];
           $profile = profile2_load_by_user($user_id);
           
           $schedule_nid = $reg_node->field_reg_schedule['und'][0]['target_id'];
           $query = new EntityFieldQuery();
           
           //Jika pilihan 'ALL' yang dipilih maka tampilkan semua
           if($gelombang_default == 'all'){
               $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'schedule')
                    ->propertyCondition('nid', $schedule_nid)
                    ->propertyCondition('status', 1);                  
           }
           else{
               $query->entityCondition('entity_type', 'node')
                    ->entityCondition('bundle', 'schedule')
                    ->propertyCondition('nid', $schedule_nid)
                    ->propertyCondition('status', 1)
                    ->fieldCondition('field_schedule_gelombang','value',$gelombang_default,'=');
           }
           
            $result = $query->execute();
            
            if(isset($result['node'])){
                $result_table = TRUE;
                $query2 = new EntityFieldQuery();
                $query2->entityCondition('entity_type', 'node')
                        ->entityCondition('bundle', 'kelulusan')
                        ->propertyCondition('status', 1)
                        ->fieldCondition('field_lulus_noreg','target_id',$reg_nid,'=');
                $result2 = $query2->execute();
                $kelulusan_nid = NULL;
                if(isset($result2['node'])){
                    $key = array_values($result2['node']);
                    $kelulusan_node = node_load($key[0]->nid);

                    $nilai = $kelulusan_node->field_lulus_nilai['und'][0]['value'];
                    $is_lulus = $kelulusan_node->field_lulus_tes['und'][0]['value'];
                    $kategori = $kelulusan_node->field_lulus_kategori['und'][0]['value'];
                    $prodi = isset($kelulusan_node->field_lulus_prodi['und'][0]['target_id'])?
                            $kelulusan_node->field_lulus_prodi['und'][0]['target_id']:NULL;
                    $kelulusan_nid = $kelulusan_node->nid;
                }
                
                $form['kelulusan']['is_new'][$reg_nid] = array(
                    '#type' => 'hidden',
                    '#value' => $kelulusan_nid
                );
                                           
           
               $form['kelulusan']['user_id'][$reg_nid] = array(
                   '#type' => 'hidden',
                   '#value' => $user_id
               );

               $noreg = $reg_node->field_reg_no['und'][0]['value'];
               $form['kelulusan']['noreg'][$reg_nid] = array(
                   '#type' => 'value',
                   '#value' => $noreg
               );

               $nama = $profile['data_pribadi']->field_personal_fullname['und'][0]['value'];
               $form['kelulusan']['nama'][$reg_nid] = array(
                   '#type' => 'value',
                   '#value' => l($nama,"user/$user_id"),
               );


               $form['kelulusan']['nilai_editable'][$reg_nid] = array(
                   '#type' => 'textfield',
                   '#size' => 5,
                   '#default_value' => isset($nilai)? $nilai:0,     
                    '#prefix' => '<div style="display:none" class="nilai_edit'.$i.'">',
                   '#suffix' => '</div>',
               );              
               $form['kelulusan']['nilai_text'][$reg_nid] = array(
                   '#type' => 'markup',                
                   '#markup' => isset($nilai)? $nilai:0,     
                    '#prefix' => '<div class="nilai_text_edit'.$i.'">',
                   '#suffix' => '</div>',
               );                                        
               
               $form['kelulusan']['is_lulus_editable'][$reg_nid] = array(
                   '#type' => 'radios',
                   '#options' => array('Tidak Lulus', 'Lulus'),
                   '#default_value' => isset($is_lulus)? $is_lulus:NULL,
                   '#prefix' => '<div style="display:none" class="is_lulus_edit'.$i.'">',
                   '#suffix' => '</div>',
               );

               $lulus_array = array('Tidak Lulus', 'Lulus');
               $form['kelulusan']['is_lulus_text'][$reg_nid] = array(
                   '#type' => 'markup',                
                   '#markup' => (isset($is_lulus) && !is_null($kelulusan_nid))? $lulus_array[$is_lulus]:'-',   
                    '#prefix' => '<div class="is_lulus_text_edit'.$i.'">',
                   '#suffix' => '</div>',
               ); 

               $form['kelulusan']['kategori_editable'][$reg_nid] = array(
                   '#type' => 'select',
                   '#options' => array(
                       'Reguler' => 'Reguler',
                       'Beasiswa Unggulan' => 'Beasiswa Unggulan',
                       'Beasiswa Gemilang' => 'Beasiswa Gemilang',
                       'Beasiswa Cemerlang' => 'Beasiswa Cemerlang',
                       ),
                   '#default_value' => isset($kategori)? $kategori:0,
                   '#prefix' => '<div style="display:none" class="kategori_edit'.$i.'">',
                   '#suffix' => '</div>',
               );
               $form['kelulusan']['kategori_text'][$reg_nid] = array(
                   '#type' => 'markup',                
                   '#markup' => isset($kategori)? $kategori:'-',
                    '#prefix' => '<div class="kategori_text_edit'.$i.'">',
                   '#suffix' => '</div>',
               ); 
               
                $form['kelulusan']['prodi_editable'][$reg_nid] = array(
                   '#type' => 'select',
                   '#options' => $prodi_options,
                   '#default_value' => isset($prodi)? $prodi:0,
                    '#prefix' => '<div style="display:none" class="prodi_edit'.$i.'">',
                   '#suffix' => '</div>',
               );
                $form['kelulusan']['prodi_text'][$reg_nid] = array(
                   '#type' => 'markup',                
                   '#markup' => isset($prodi)? $prodi_options[$prodi]:'-',   
                    '#prefix' => '<div class="prodi_text_edit'.$i.'">',
                   '#suffix' => '</div>',
               ); 
                
                $form['kelulusan']['edit'][$reg_nid] = array(
                   '#type' => 'markup',
                   '#markup' => "<a href=#>edit</a>",
                   '#prefix' => '<div class="edit'.$i.'">',
                   '#suffix' => '</div>',
               );
                $form['kelulusan']['cancel'][$reg_nid] = array(
                   '#type' => 'markup',
                   '#markup' => "<a href=#>cancel</a>",
                    '#prefix' => '<div style="display:none" class="cancel'.$i.'">',
                   '#suffix' => '</div>',
               );
                $i++;
            }
       }
       
       if($result_table){
           $form['submit'] = array(
                '#type' => 'submit',
                '#value' => 'Submit',
               '#attributes' => array('class' => array('submit-form-edit'),'style'=>'display:none'),
            );
       }
       
   }
  
   drupal_add_js(drupal_get_path('module', 'admission_user').'/script.js');
   
    return $form;
}

function theme_kelulusan_form(&$variables){
    $form = $variables['form'];
    
    $output = '';
    
    $header = array(
        array('data' => t('No.'),),
        array('data' => t('No.Registrasi')),
        array('data' => t('Nama')),
        array('data' => t('Nilai')),
        array('data' => t('Kelulusan')),
         array('data' => t('Kategori')),
        array('data' => t('Program Studi')),
        array('data' => ''),
        );
    
     $output .= drupal_render($form['filter']);
     $rows = array();
    if(isset($form['kelulusan']['noreg'])){
        
        $no = 1;
        
        foreach(element_children($form['kelulusan']['noreg']) as $reg_nid){
            $row = array();      
            $row[] = array('data' => $no++);
            $row[] = array('data' => l($form['kelulusan']['noreg'][$reg_nid]['#value'],"node/$reg_nid"));
            $row[] = array('data' => $form['kelulusan']['nama'][$reg_nid]['#value']);
            $row[] = array('data' => drupal_render($form['kelulusan']['nilai_editable'][$reg_nid]).
                ' '.drupal_render($form['kelulusan']['nilai_text'][$reg_nid]));
            $row[] = array('data' => drupal_render($form['kelulusan']['is_lulus_editable'][$reg_nid]).
                 ' '.drupal_render($form['kelulusan']['is_lulus_text'][$reg_nid]));
            $row[] = array('data' => drupal_render($form['kelulusan']['kategori_editable'][$reg_nid]).
                 ' '.drupal_render($form['kelulusan']['kategori_text'][$reg_nid]));
            $row[] = array('data' => drupal_render($form['kelulusan']['prodi_editable'][$reg_nid]).
                 ' '.drupal_render($form['kelulusan']['prodi_text'][$reg_nid]));
            $row[] = array('data' => drupal_render($form['kelulusan']['edit'][$reg_nid]).
                ' '.drupal_render($form['kelulusan']['cancel'][$reg_nid]));
            $rows[] = $row;
        }             
    }          
    
    $output .= theme('table',
            array(
                'header' => $header,
                'rows' => $rows,
                'empty' => 'No data is available',)
        );  
    $output .= drupal_render_children($form);
     
    return $output;
}

function kelulusan_form_submit($form, &$form_state){
    include drupal_get_path('module', 'admission_user').'/admission_user.api.inc';
    $submit = $form_state['input']['op'];
    
    variable_set('kelulusan', $form_state['values']);
    
    switch ($submit) {
        case 'Submit':
            $form_state['input']['kelulusan'] = $form_state['values']['kelulusan'];
            $kelulusan = $form_state['values']['kelulusan'];
            foreach($kelulusan['noreg'] as $key => $value){
                if(!is_null($kelulusan['is_lulus_editable'][$key])){
                    create_node_kelulusan(
                        $kelulusan['is_new'][$key], 
                        $key,                        
                        $kelulusan['nilai_editable'][$key], 
                        $kelulusan['is_lulus_editable'][$key],
                        $kelulusan['kategori_editable'][$key],
                        $kelulusan['prodi_editable'][$key]);
                }              
            }
            
            drupal_set_message('success');
    }
}
