<?php

function survey_form(){
   global $user;
   
   $survey = node_load_multiple(array(), array('type' => 'survey', 'uid' => $user->uid));
   
   if($survey){
       $form['survey'] = array(
           '#type' => 'value',
           '#value' => '<p>Anda sudah menjawab survey kami.</p>'
       );
       
       return $form;
   }
   
  $dev_questions = array(
        1 => 'Membantu proses pendaftaran',
        2 => 'Mudah dalam penggunaanya',
        3 => 'Lengkap informasi pendaftarannya',
        4 => 'Secara umum anda menilai aplikasi ini'
    );
    
   foreach($dev_questions as $key => $question){
       $form['aplikasi'][$key] = array(
           '#type' => 'value',
           '#value' => $question
       );
       
       $form['aplikasi'][$key]['jawab_'.$key] = array(
          '#type' => 'radios',
          '#options' => array(1=>'',2=>'',3=>'',4=>'',5=>''),
          '#attributes' => array('class' => array('container-inline')), 
          );     
   }
   
   $form['aplikasi']['saran'] = array(
       '#title' => 'Saran-saran:',
        '#type' => 'textarea',
        '#size' => 5
    );  
   
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'submit'
    );   
    
   return $form;
}

function theme_survey_form(&$variables){
    $output = '';
    
     $form = $variables['form'];
    
    $header_dev = array(
        'No.','Aplikasi','1 | 2 | 3 |4 | 5',
    );      
    
    if(isset($form['survey'])){
        $output .= $form['survey']['#value'];
    }
    else{
        $output .= '<u><h2>Survey Aplikasi Pendaftaran Online</h2></u>';
        
        $rows = array();
   
        for($i = 1; $i < 5; $i++){
            $row = array();
            $row[] = array('data' => $i);
            $row[] = array('data' => $form['aplikasi'][$i]['#value']);

            $row[] = array('data' => drupal_render($form['aplikasi'][$i]['jawab_'.$i]));
            $rows[] = $row;
        }

        $output .= theme('table',
                array(
                    'header' => $header_dev,
                    'rows' => $rows
                ));

        $output .= drupal_render($form['aplikasi']['saran']);
    }
      
    $output .= drupal_render_children($form);
    return $output;
}

function survey_form_submit($form, &$form_state){
    include drupal_get_path('module', 'admission_user').'/admission_user.api.inc';
    
    $input = $form_state['values'];
    create_survey_node($input);
    drupal_set_message(t('Thank You for your participation.'));
}
